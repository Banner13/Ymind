/**
 * struct vb2_buffer - 表示视频缓冲区。
 * @vb2_queue：指向 &struct vb2_queue 的指针，其中包含该驱动器所属的队列。
 * @index：缓冲区的 ID 号。
 * @type：缓冲区类型。
 * @memory：传递实际数据的方法。
 * @num_planes：内部驱动程序队列中缓冲区的平面数。
 * @timestamp：以 ns 为单位的帧时间戳。
 * @request：与该缓冲区相关联的请求。
 * @req_obj：用于将此缓冲区与请求绑定。该请求对象有一个 refcount。
 */