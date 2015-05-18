#include "../header/include.h"
#include "gp_fifo.h"

void gp_fifo_init(GP_FIFO *fifo_ptr, void *buffer_ptr, u32 buffer_size, u32 fifo_size)
{
	u32 i;

	fifo_ptr->buffer = buffer_ptr;
	fifo_ptr->write_ptr = fifo_ptr->buffer;
	fifo_ptr->read_ptr = fifo_ptr->buffer;
	fifo_ptr->buffer_size = buffer_size;
	fifo_ptr->fifo_size = fifo_size;
	fifo_ptr->fifo_empty = 1;
	fifo_ptr->fifo_full = 0;
	for(i=0; i<buffer_size*fifo_size; i++)
		fifo_ptr->buffer[i] = 0;
}

void gp_fifo_push(GP_FIFO *fifo_ptr, void *buffer_ptr)
{
	if(!fifo_ptr->fifo_full)
	{
		memcpy__(fifo_ptr->write_ptr, buffer_ptr, fifo_ptr->buffer_size);
		fifo_ptr->write_ptr += fifo_ptr->buffer_size;
		if(fifo_ptr->write_ptr >= fifo_ptr->buffer+fifo_ptr->buffer_size*fifo_ptr->fifo_size)
			fifo_ptr->write_ptr = fifo_ptr->buffer;
		if(fifo_ptr->write_ptr == fifo_ptr->read_ptr)
		{
			fifo_ptr->fifo_full = 1;
		}
		fifo_ptr->fifo_empty = 0;
	}
}

void gp_fifo_pop(GP_FIFO *fifo_ptr, void *buffer_ptr)
{
	if(!fifo_ptr->fifo_empty)
	{
		memcpy__(buffer_ptr, fifo_ptr->read_ptr, fifo_ptr->buffer_size);
		fifo_ptr->read_ptr += fifo_ptr->buffer_size;
		if(fifo_ptr->read_ptr >= fifo_ptr->buffer+fifo_ptr->buffer_size*fifo_ptr->fifo_size)
			fifo_ptr->read_ptr = fifo_ptr->buffer;
		if(fifo_ptr->read_ptr == fifo_ptr->write_ptr)
		{
			fifo_ptr->fifo_empty = 1;
		}
		fifo_ptr->fifo_full = 0;
	}
}

