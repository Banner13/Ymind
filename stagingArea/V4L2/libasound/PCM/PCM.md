``` author
/**
 * \file pcm/pcm.c
 * \ingroup PCM
 * \brief PCM Interface
 * \author Jaroslav Kysela <perex@perex.cz>
 * \author Abramo Bagnara <abramo@alsa-project.org>
 * \date 2000-2001
 *
 * PCM Interface is designed to write or read digital audio frames. A
 * frame is the data unit converted into/from sound in one time unit
 * (1/rate seconds), by example if you set your playback PCM rate to
 * 44100 you'll hear 44100 frames per second. The size in bytes of a
 * frame may be obtained from bits needed to store a sample and
 * channels count.
 *
 * See the \ref pcm page for more details.
 */
/*
 *  PCM Interface - main file
 *  Copyright (c) 1998 by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) 2000 by Abramo Bagnara <abramo@alsa-project.org>
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
```
/*! \page pcm PCM (digital audio) interface

<P>Although abbreviation PCM stands for Pulse Code Modulation, we are
understanding it as general digital audio processing with volume samples
generated in continuous time periods.</P>

<P>The analog signal is recorded via analog to digital converters (ADC).
The digital value (de-facto a volume at a specific time) obtained
from ADC can be further processed. The following picture shows a perfect
sinus waveform:</P>

<BR>
\image html ![[wave1.gif]]

<P>Next image shows digitized representation:</P>

<BR>
\image html ![[wave2.gif]]

<P>As you may see, the quality of digital audio signal depends on the time
(recording rate) and voltage resolution (usually in an linear integer
representation with basic unit one bit).</P>

<P>The stored digital signal can be converted back to voltage (analog)
representation via digital to analog converters (DAC).</P>

<P>One digital value is called sample. More samples are collected to frames
(frame is terminology for ALSA) depending on count of converters used at one
specific time. One frame might contain one sample (when only one converter is
used - mono) or more samples (for example: stereo has signals from two converters
recorded at same time). Digital audio stream contains collection of frames
recorded at boundaries of continuous time periods.</P>

\section pcm_general_overview General overview

ALSA uses the ring buffer to store outgoing (playback) and incoming (capture,
record) samples. There are two pointers being maintained to allow
a precise communication between application and device pointing to current
processed sample by hardware and last processed sample by application.
The modern audio chips allow to program the transfer time periods.
It means that the stream of samples is divided to small chunks. Device
acknowledges to application when the transfer of a chunk is complete.

\section pcm_transfer Transfer methods in UNIX environments

In the UNIX environment, data chunk acknowledges are received via standard I/O
calls or event waiting routines (poll or select function). To accomplish
this list, the asynchronous notification of acknowledges should be listed
here. The ALSA implementation for these methods is described in
the \ref alsa_transfers section.

\subsection pcm_transfer_io Standard I/O transfers

The standard I/O transfers are using the read (see 'man 2 read') and write
(see 'man 2 write') C functions. There are two basic behaviours of these
functions - blocked and non-blocked (see the O_NONBLOCK flag for the
standard C open function - see 'man 2 open'). In non-blocked behaviour,
these I/O functions never stops, they return -EAGAIN error code, when no
data can be transferred (the ring buffer is full in our case). In blocked
behaviour, these I/O functions stop and wait until there is a room in the
ring buffer (playback) or until there are a new samples (capture). The ALSA
implementation can be found in the \ref alsa_pcm_rw section.

\subsection pcm_transfer_event Event waiting routines

The poll or select functions (see 'man 2 poll' or 'man 2 select' for further
details) allows to receive requests/events from the device while
an application is waiting on events from other sources (like keyboard, screen,
network etc.), too. \ref snd_pcm_poll_descriptors can be used to get file
descriptors to poll or select on (note that wait direction might be different
than expected - do not use only returned file descriptors, but handle
events member as well - see \ref snd_pcm_poll_descriptors function
description for more details and \ref snd_pcm_poll_descriptors_revents for
events demangling). The implemented transfer routines can be found in
the \ref alsa_transfers section.

\subsection pcm_transfer_async Asynchronous notification

ALSA driver and library knows to handle the asynchronous notifications over
the SIGIO signal. This signal allows to interrupt application and transfer
data in the signal handler. For further details see the sigaction function
('man 2 sigaction'). The section \ref pcm_async describes the ALSA API for
this extension. The implemented transfer routines can be found in the
\ref alsa_transfers section.

\section pcm_open_behaviour Blocked and non-blocked open

The ALSA PCM API uses a different behaviour when the device is opened
with blocked or non-blocked mode. The mode can be specified with
\a mode argument in #snd_pcm_open() function.
The blocked mode is the default (without #SND_PCM_NONBLOCK mode).
In this mode, the behaviour is that if the resources have already used
with another application, then it blocks the caller, until resources are
free. The non-blocked behaviour (with #SND_PCM_NONBLOCK)
doesn't block the caller in any way and returns -EBUSY error when the
resources are not available. Note that the mode also determines the
behaviour of standard I/O calls, returning -EAGAIN when non-blocked mode is
used and the ring buffer is full (playback) or empty (capture).
The operation mode for I/O calls can be changed later with
the #snd_pcm_nonblock() function.

\section pcm_async Asynchronous mode

There is also possibility to receive asynchronous notification after
specified time periods. You may see the #SND_PCM_ASYNC
mode for #snd_pcm_open() function and
#snd_async_add_pcm_handler() function for further details.

\section pcm_handshake Handshake between application and library

The ALSA PCM API design uses the states to determine the communication
phase between application and library. The actual state can be determined
using #snd_pcm_state() call. There are these states:

\par SND_PCM_STATE_OPEN
The PCM device is in the open state. After the #snd_pcm_open() open call,
the device is in this state. Also, when #snd_pcm_hw_params() call fails,
then this state is entered to force application calling 
#snd_pcm_hw_params() function to set right communication
parameters.

\par SND_PCM_STATE_SETUP
The PCM device has accepted communication parameters and it is waiting
for #snd_pcm_prepare() call to prepare the hardware for
selected operation (playback or capture).

\par SND_PCM_STATE_PREPARED
The PCM device is prepared for operation. Application can use
#snd_pcm_start() call, write or read data to start
the operation.

\par SND_PCM_STATE_RUNNING
The PCM device has been started and is running. It processes the samples. The stream can
be stopped using the #snd_pcm_drop() or
#snd_pcm_drain() calls.

\par SND_PCM_STATE_XRUN
The PCM device reached overrun (capture) or underrun (playback).
You can use the -EPIPE return code from I/O functions
(#snd_pcm_writei(), #snd_pcm_writen(), #snd_pcm_readi(), #snd_pcm_readn())
to determine this state without checking
the actual state via #snd_pcm_state() call. It is recommended to use
the helper function #snd_pcm_recover() to recover from this state, but you can also use #snd_pcm_prepare(),
#snd_pcm_drop() or #snd_pcm_drain() calls.

\par SND_PCM_STATE_DRAINING
The device is in this state when application using the capture mode
called #snd_pcm_drain() function. Until all data are
read from the internal ring buffer using I/O routines
(#snd_pcm_readi(), #snd_pcm_readn()),
then the device stays in this state.

\par SND_PCM_STATE_PAUSED
The device is in this state when application called
the #snd_pcm_pause() function until the pause is released.
Not all hardware supports this feature. Application should check the
capability with the #snd_pcm_hw_params_can_pause().

\par SND_PCM_STATE_SUSPENDED
The device is in the suspend state provoked with the power management
system. The stream can be resumed using #snd_pcm_resume()
call, but not all hardware supports this feature. Application should check
the capability with the #snd_pcm_hw_params_can_resume().
In other case, the calls #snd_pcm_prepare(),
#snd_pcm_drop(), #snd_pcm_drain() can be used
to leave this state.

\par SND_PCM_STATE_DISCONNECTED
The device is physicaly disconnected. It does not accept any I/O calls in this state.

\section pcm_formats PCM formats

The full list of formats present the #snd_pcm_format_t type.
The 24-bit linear samples use 32-bit physical space, but the sample is
stored in the lower three bytes. Some hardware does not support processing of full
range, thus you may get the significant bits for linear samples via
#snd_pcm_hw_params_get_sbits() function. The example: ICE1712
chips support 32-bit sample processing, but low byte is ignored (playback)
or zero (capture). The function snd_pcm_hw_params_get_sbits()
returns 24 in this case.

\section alsa_transfers ALSA transfers

There are two methods to transfer samples in application. The first method
is the standard read / write one. The second method, uses the direct audio
buffer to communicate with the device while ALSA library manages this space
itself. You can find examples of all communication schemes for playback
in \ref example_test_pcm "Sine-wave generator example". To complete the
list, we should note that #snd_pcm_wait() function contains
embedded poll waiting implementation.

\subsection alsa_pcm_rw Read / Write transfer

There are two versions of read / write routines. The first expects the
interleaved samples at input (#SND_PCM_ACCESS_RW_INTERLEAVED access method),
and the second one expects non-interleaved (samples in separated buffers -
#SND_PCM_ACCESS_RW_NONINTERLEAVED access method) at input. There are these
functions for interleaved transfers: #snd_pcm_writei()
#snd_pcm_readi(). For non-interleaved transfers, there are
these functions: #snd_pcm_writen() and #snd_pcm_readn().

\subsection alsa_mmap_rw Direct Read / Write transfer (via mmap'ed areas)

Three kinds of organization of ring buffer memory areas exist in ALSA API.
Access #SND_PCM_ACCESS_MMAP_INTERLEAVED has interleaved samples. Access
#SND_PCM_ACCESS_MMAP_NONINTERLEAVED expects continous sample areas for
one channel. Access #SND_PCM_ACCESS_MMAP_COMPLEX does not fit to interleaved
and non-interleaved ring buffer organization.

There are two functions for this kind of transfer. Application can get an
access to memory areas via #snd_pcm_mmap_begin() function.
This function returns the areas (single area is equal to a channel)
containing the direct pointers to memory and sample position description
in #snd_pcm_channel_area_t structure. After application
transfers the data in the memory areas, then it must be acknowledged
the end of transfer via #snd_pcm_mmap_commit() function
to allow the ALSA library update the pointers to ring buffer. This kind of
communication is also called "zero-copy", because the device does not require
to copy the samples from application to another place in system memory.

If you like to use the compatibility functions in mmap mode, there are
read / write routines equaling to standard read / write transfers. Using
these functions discards the benefits of direct access to memory region.
See the #snd_pcm_mmap_readi(),
#snd_pcm_mmap_writei(), #snd_pcm_mmap_readn()
and #snd_pcm_mmap_writen() functions. These functions use
#snd_pcm_areas_copy() internally.

\section pcm_errors Error codes

\par -EPIPE

This error means xrun (underrun for playback or overrun for capture).
The underrun can happen when an application does not feed new samples
in time to alsa-lib (due CPU usage). The overrun can happen when
an application does not take new captured samples in time from alsa-lib.

\par -ESTRPIPE

This error means that system has suspended drivers. The application
should wait in loop when snd_pcm_resume() != -EAGAIN and then
call snd_pcm_prepare() when snd_pcm_resume() return an error code.
If snd_pcm_resume() does not fail (a zero value is returned), driver
supports resume and the snd_pcm_prepare() call can be ommited.

\par -EBADFD

This error means that the device is in a bad state. It means that
the handshake between application and alsa-lib is corrupted.

\par -ENOTTY, -ENODEV

This error can happen when device is physically removed (for example
some hotplug devices like USB or PCMCIA, CardBus or ExpressCard
can be removed on the fly).

\par -ENODATA

This error can happen if the device data transfer is dependent on
an external condition and that condition is not met. For example,
PCM device for echo reference as described by SND_USE_CASE_MOD_ECHO_REF
UCM token, may return -ENODATA if the linked playback stream has not been
started.

There is no defined recovery or event mechanism to signal the data / link
availability at the moment. The PCM must be completely restarted until
the mechanism is designed. The #snd_pcm_recover() function cannot be
used for this.

\section pcm_params Managing parameters

The ALSA PCM device uses two groups of PCM related parameters. The hardware
parameters contains the stream description like format, rate, count of
channels, ring buffer size etc. The software parameters contains the
software (driver) related parameters. The communication behaviour can be
controlled via these parameters, like automatic start, automatic stop,
interrupting (chunk acknowledge) etc. The software parameters can be
modified at any time (when valid hardware parameters are set). It includes
the running state as well.

\subsection pcm_hw_params Hardware related parameters

The ALSA PCM devices use the parameter refining system for hardware
parameters - #snd_pcm_hw_params_t. It means, that
application choose the full-range of configurations at first and then
application sets single parameters until all parameters are elementary
(definite).

\par Access modes

ALSA knows about five access modes. The first three can be used for direct
communication. The access mode #SND_PCM_ACCESS_MMAP_INTERLEAVED
determines the direct memory area and interleaved sample organization.
Interleaved organization means, that samples from channels are mixed together.
The access mode #SND_PCM_ACCESS_MMAP_NONINTERLEAVED
determines the direct memory area and non-interleaved sample organization.
Each channel has a separate buffer in the case. The complex direct memory
organization represents the #SND_PCM_ACCESS_MMAP_COMPLEX
access mode. The sample organization does not fit the interleaved or
non-interleaved access modes in the case. The last two access modes
describes the read / write access methods.
The #SND_PCM_ACCESS_RW_INTERLEAVED access represents the read /
write interleaved access and the #SND_PCM_ACCESS_RW_NONINTERLEAVED
represents the non-interleaved access.

\par Formats

The full list of formats is available in #snd_pcm_format_t
enumeration.

\subsection pcm_sw_params Software related parameters

These parameters - #snd_pcm_sw_params_t can be modified at
any time including the running state.

\par Minimum available count of samples

This parameter controls the wakeup point. If the count of available samples
is equal or greater than this value, then application will be activated.

\par Timestamp mode

The timestamp mode specifies, if timestamps are activated. Currently, only
#SND_PCM_TSTAMP_NONE and #SND_PCM_TSTAMP_MMAP
modes are known. The mmap mode means that timestamp is taken
on every period time boundary. Corresponding position in the ring buffer
assigned to timestamp can be obtained using #snd_pcm_htimestamp() function.

\par Transfer align

The read / write transfers can be aligned to this sample count. The modulo
is ignored by device. Usually, this value is set to one (no align).

\par Start threshold

The start threshold parameter is used to determine the start point in
stream. For playback, if samples in ring buffer is equal or greater than
the start threshold parameters and the stream is not running, the stream will
be started automatically from the device. For capture, if the application wants
to read count of samples equal or greater then the stream will be started.
If you want to use explicit start (#snd_pcm_start), you can
set this value greater than ring buffer size (in samples), but use the
constant MAXINT is not a bad idea.

\par Stop threshold

Similarly, the stop threshold parameter is used to automatically stop
the running stream, when the available samples crosses this boundary.
It means, for playback, the empty samples in ring buffer and for capture,
the filled (used) samples in ring buffer.

\par Silence threshold

The silence threshold specifies count of samples filled with silence
ahead of the current application pointer for playback. It is usable
for applications when an overrun is possible (like tasks depending on
network I/O etc.). If application wants to manage the ahead samples itself,
the #snd_pcm_rewind() function allows to forget the last
samples in the stream.

\section pcm_status Obtaining stream status

The stream status is stored in #snd_pcm_status_t structure.
These parameters can be obtained: the current stream state -
#snd_pcm_status_get_state(), timestamp of trigger -
#snd_pcm_status_get_trigger_tstamp(), timestamp of last
pointer update #snd_pcm_status_get_tstamp(), delay in samples -
#snd_pcm_status_get_delay(), available count in samples -
#snd_pcm_status_get_avail(), maximum available samples -
#snd_pcm_status_get_avail_max(), ADC over-range count in
samples - #snd_pcm_status_get_overrange(). The last two
parameters - avail_max and overrange are reset to zero after the status
call.

\subsection pcm_status_fast Obtaining stream state fast and update r/w pointer

<p>
The function #snd_pcm_avail_update() updates the current
available count of samples for writing (playback) or filled samples for
reading (capture). This call is mandatory for updating actual r/w pointer.
Using standalone, it is a light method to obtain current stream position,
because it does not require the user <-> kernel context switch, but the value
is less accurate, because ring buffer pointers are updated in kernel drivers
only when an interrupt occurs. If you want to get accurate stream state,
use functions #snd_pcm_avail(), #snd_pcm_delay() or #snd_pcm_avail_delay().
</p>
<p>
The function #snd_pcm_avail() reads the current hardware pointer
in the ring buffer from hardware and calls #snd_pcm_avail_update() then.
</p>
<p>
The function #snd_pcm_delay() returns the delay in samples.
For playback, it means count of samples in the ring buffer before
the next sample will be sent to DAC. For capture, it means count of samples
in the ring buffer before the next sample will be captured from ADC. It works
only when the stream is in the running or draining (playback only) state.
Note that this function does not update the current r/w pointer for applications,
so the function #snd_pcm_avail_update() must be called afterwards
before any read/write begin+commit operations.
</p>
<p>
The function #snd_pcm_avail_delay() combines #snd_pcm_avail() and
#snd_pcm_delay() and returns both values in sync.
</p>

\section pcm_action Managing the stream state

The following functions directly and indirectly affect the stream state:

\par snd_pcm_hw_params
The #snd_pcm_hw_params() function brings the stream state
to #SND_PCM_STATE_SETUP
if successfully finishes, otherwise the state #SND_PCM_STATE_OPEN
is entered.
When it is brought to SETUP state, this function automatically
calls #snd_pcm_prepare() function to bring to the PREPARED state
as below.

\par snd_pcm_prepare
The #snd_pcm_prepare() function enters from #SND_PCM_STATE_SETUP
to the #SND_PCM_STATE_PREPARED after a successful finish.

\par snd_pcm_start
The #snd_pcm_start() function enters
the #SND_PCM_STATE_RUNNING after a successful finish.

\par snd_pcm_drop
The #snd_pcm_drop() function enters the
#SND_PCM_STATE_SETUP state.

\par snd_pcm_drain
The #snd_pcm_drain() function enters the
#SND_PCM_STATE_DRAINING, if
the capture device has some samples in the ring buffer otherwise
#SND_PCM_STATE_SETUP state is entered.

\par snd_pcm_pause
The #snd_pcm_pause() function enters the
#SND_PCM_STATE_PAUSED or #SND_PCM_STATE_RUNNING.

\par snd_pcm_writei, snd_pcm_writen
The #snd_pcm_writei() and #snd_pcm_writen()
functions can conditionally start the stream -
#SND_PCM_STATE_RUNNING. They depend on the start threshold
software parameter.

\par snd_pcm_readi, snd_pcm_readn
The #snd_pcm_readi() and #snd_pcm_readn()
functions can conditionally start the stream -
#SND_PCM_STATE_RUNNING. They depend on the start threshold
software parameter.

\section pcm_sync Streams synchronization

There are two functions allowing link multiple streams together. In the
case, the linking means that all operations are synchronized. Because the
drivers cannot guarantee the synchronization (sample resolution) on hardware
lacking this feature, the #snd_pcm_info_get_sync() function
returns synchronization ID - #snd_pcm_sync_id_t, which is equal
for hardware synchronized streams. When the #snd_pcm_link()
function is called, all operations managing the stream state for these two
streams are joined. The opposite function is #snd_pcm_unlink().

\section pcm_thread_safety Thread-safety

When the library is configured with the proper option, some PCM functions
(e.g. #snd_pcm_avail_update()) are thread-safe and can be called concurrently
from multiple threads.  Meanwhile, some functions (e.g. #snd_pcm_hw_params())
aren't thread-safe, and application needs to call them carefully when they
are called from multiple threads.  In general, all the functions that are
often called during streaming are covered as thread-safe.

This thread-safe behavior can be disabled also by passing 0 to the environment
variable LIBASOUND_THREAD_SAFE, e.g.
\code
LIBASOUND_THREAD_SAFE=0 aplay foo.wav
\endcode
for making the debugging easier.

\section pcm_dev_names PCM naming conventions

The ALSA library uses a generic string representation for names of devices.
The devices might be virtual, physical or a mix of both. The generic string
is passed to #snd_pcm_open() or #snd_pcm_open_lconf().
It contains two parts: device name and arguments. Devices and arguments are described
in configuration files. The usual place for default definitions is at /usr/share/alsa/alsa.conf.
For detailed descriptions about integrated PCM plugins look to \ref pcm_plugins.

\subsection pcm_dev_names_default Default device

The default device is equal to plug plugin with hw plugin as slave. The defaults are
used:

\code
defaults.pcm.card 0
defaults.pcm.device 0
defaults.pcm.subdevice -1
\endcode

These defaults can be freely overwritten in local configuration files.

Example:

\code
default
\endcode

\subsection pcm_dev_names_hw HW device

The hw device description uses the hw plugin. The three arguments (in order: CARD,DEV,SUBDEV)
specify card number or identifier, device number and subdevice number (-1 means any).

Example:

\code
hw
hw:0
hw:0,0
hw:supersonic,1
hw:soundwave,1,2
hw:DEV=1,CARD=soundwave,SUBDEV=2
\endcode

\subsection pcm_dev_names_plughw Plug->HW device

The plughw device description uses the plug plugin and hw plugin as slave. The arguments
are same as for hw device.

Example:

\code
plughw
plughw:0
plughw:0,0
plughw:supersonic,1
plughw:soundwave,1,2
plughw:DEV=1,CARD=soundwave,SUBDEV=2
\endcode

\subsection pcm_dev_names_plug Plug device

The plug device uses the plug plugin. The one SLAVE argument specifies the slave plugin.

Example:

\code
plug:mypcmdef
plug:hw
plug:'hw:0,0'
plug:SLAVE=hw
\endcode

\subsection pcm_dev_names_shm Shared memory device

The shm device uses the shm plugin. The two arguments (in order: SOCKET,PCM) specify
UNIX socket name (for example /tmp/alsa.socket) for server communication and server's PCM name.

Example:

\code
shm:'/tmp/alsa.sock',default
shm:SOCKET='/tmp/alsa.sock',PCM=default
\endcode

\subsection pcm_dev_names_tee Tee device

The tee device stores contents of a stream to given file plus transfers it to given slave plugin.
The three arguments (in order: SLAVE,FILE,FORMAT) specify slave plugin, filename and file format.

Example:

\code
tee:hw,'/tmp/out.raw',raw
\endcode

\subsection pcm_dev_names_file File device

The file device is file plugin with null plugin as slave. The arguments (in order: FILE,FORMAT)
specify filename and file format.

Example:

\code
file:'/tmp/out.raw',raw
\endcode

\subsection pcm_dev_names_null Null device

The null device is null plugin. This device has not any arguments.


\section pcm_examples Examples

The full featured examples with cross-links can be found in Examples section
(see top of page):

\anchor example_test_pcm
\par Sine-wave generator
\par
alsa-lib/test/pcm.c example shows various transfer methods for the playback direction.

\par Minimalistic PCM playback code
\par
alsa-lib/test/pcm_min.c example shows the minimal code to produce a sound.

\par Latency measuring tool
\par
alsa-lib/test/latency.c example shows the measuring of minimal latency between capture and
playback devices.

*/

/**
\example ../../test/pcm.c
*/
/**
\example ../../test/pcm_min.c
*/
/**
\example ../../test/latency.c
*/

