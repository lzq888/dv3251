#ifndef __GP_FIFO_H__
#define	__GP_FIFO_H__

typedef	struct
{
	u8	*write_ptr;		// 写指针
	u8	*read_ptr;		// 读指针
	u8	*buffer;		// 指向FIFO首元素地址
	u32	buffer_size;	// FIFO元素的大小
	u32	fifo_size;		// FIFO大小
	int fifo_empty;		// FIFO空标志
	int fifo_full;		// FIFO满标志
} GP_FIFO;

void gp_fifo_init(GP_FIFO *fifo_ptr, void *buffer_ptr, u32 buffer_size, u32 fifo_size);
void gp_fifo_push(GP_FIFO *fifo_ptr, void *buffer_ptr);
void gp_fifo_pop(GP_FIFO *fifo_ptr, void *buffer_ptr);

#endif
