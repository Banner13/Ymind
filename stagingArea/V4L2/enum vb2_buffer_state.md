/**
 * enum vb2_buffer_state - current video buffer state.
 * @VB2_BUF_STATE_DEQUEUED:	buffer under userspace control.
 * @VB2_BUF_STATE_IN_REQUEST:	buffer is queued in media request.
 * @VB2_BUF_STATE_PREPARING:	buffer is being prepared in videobuf2.
 * @VB2_BUF_STATE_QUEUED:	buffer queued in videobuf2, but not in driver.
 * @VB2_BUF_STATE_ACTIVE:	buffer queued in driver and possibly used
 *				in a hardware operation.
 * @VB2_BUF_STATE_DONE:		buffer returned from driver to videobuf2, but
 *				not yet dequeued to userspace.
 * @VB2_BUF_STATE_ERROR:	same as above, but the operation on the buffer
 *				has ended with an error, which will be reported
 *				to the userspace when it is dequeued.
 */
enum vb2_buffer_state {
	VB2_BUF_STATE_DEQUEUED,
	VB2_BUF_STATE_IN_REQUEST,
	VB2_BUF_STATE_PREPARING,
	VB2_BUF_STATE_QUEUED,
	VB2_BUF_STATE_ACTIVE,
	VB2_BUF_STATE_DONE,
	VB2_BUF_STATE_ERROR,
};