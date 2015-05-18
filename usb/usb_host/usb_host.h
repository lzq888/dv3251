/*
 * usb_host.h
 *
 *  Created on: 2013Äê10ÔÂ24ÈÕ
 *      Author: jingcunxu
 */

#ifndef USB_HOST_H_
#define USB_HOST_H_


#define MAX_EP 	2


typedef struct
{
    u16  vid, pid;       // Vendor ID and Product ID
    u8  bclass;
    u8  num_of_eps;      // actual number endpoint from slave
    u8  id_mft;          // Manufacturer ID
    u8  id_pdt;          // Product ID
    u8  id1;
    u8  id2;
    u8  ep_addr[MAX_EP];   // bool 7 = 1 = use PID_IN,
    u8  attr[MAX_EP];     // ISO | Bulk | Interrupt | Control
    u16 pay_load[MAX_EP];  // ISO range: 1-1023, Bulk: 1-64, etc
    u16 interval[MAX_EP]; // polling interval (for LS)
    u8  data1[MAX_EP];    // DataToggle value
} USBDEV, *PUSBDEV;


// Standard Device Descriptor
typedef struct
{
    u8  length;
    u8  descriptor_type;
    u16 bcd_usb;
    u8  device_class;
    u8  device_subclass;
    u8  device_protocol;
    u8  maxpacket_size0;
    u16 id_vendor;
    u16 id_product;
    u16 bcd_device;
    u8  manufacturer;
    u8  product;
    u8  serial_number;
    u8  num_configurations;
} SDEV_DESC, *P_DEV_DESC;


// Standard Configuration Descriptor
typedef struct
{
    u8  length;                // Size of descriptor in u8
    u8  type;                  // Configuration
    u16 t_length;              // Total length
    u8  num_intf;              // Number of interface
    u8  cv;                    // bConfigurationValue
    u8  index;                 // iConfiguration
    u8  attr;                  // Configuration Characteristic
    u8  max_power;             // Power config
} SCFG_DESC, *P_SCFG_DESC;



// Standard Interface Descriptor
typedef struct
{
    u8 length;
    u8 type;
    u8 num;
    u8 alt_tring;
    u8 end_points;
    u8 iclass;
    u8 sub;
    u8 proto;
    u8 index;
} SINTF_DESC, *P_INTF_DESC;


// Standard EndPoint Descriptor
typedef struct
{
    u8  length;
    u8  type;
    u8  ep_addr;
    u8  attr;
    u16 pay_load;               // low-speed this must be 0x08
    u8  interval;
} SEP_DESC, *P_EP_DESC;


USBDEV  		udev;
P_DEV_DESC  	p_dev;//Éè±¸ÃèÊö·û
P_SCFG_DESC 	p_cfg;//ÅäÖÃÃèÊö·û
P_INTF_DESC 	p_ifc;//½Ó¿ÚÃèÊö·û
P_EP_DESC  		p_enp;//¶ËµãÃèÊö·û


#define FULL_SPEED		0
#define HIGH_SPEED		1

u8 usb_type;


void usb_detect_init();
u8 usb_read(u8 *rbuf,u32 lba,u32 offset);
u8 usb_write(u8 *wbuf,u32 lba,u32 offset);
u8 usb_host_enum(void);
void usb_irq_isr(void);



#endif /* USB_HOST_H_ */
