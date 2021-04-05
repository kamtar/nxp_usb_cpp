/*
 * usb_misc.hpp
 *
 *  Created on: 25 Feb 2021
 *      Author: Kamtar
 */

#ifndef LIB_CPP_USB_USB_MISC_HPP_
#define LIB_CPP_USB_USB_MISC_HPP_
#include <stdint.h>
#include <stddef.h>

#define PACKED __attribute__((packed))

namespace KamtarUSB {

enum class DescType : uint8_t {
	Any = 0x00,    // Wildcard for searches
	Device = 0x01,
	Conf = 0x02,
	String = 0x03,
	Interface = 0x04,
	Endpoint = 0x05,
	DeviceQualifier = 0x06,
	OtherSpeedConf = 0x07,
	InterfacePower = 0x08,
	OnTheGo = 0x09,
	Debug = 0x0A,
	InterfaceAssociation = 0x0B,
	HID = 0x21,
	Report = 0x22,
	Physical = 0x23,
	ClassInterface = 0x24,
	HUB = 0x29
};

enum class ClassCodes : uint8_t {
	Device = 0x00,
	Audio = 0x01,
	CDC_Control = 0x02,
	HID = 0x03,
	Physical = 0x05,
	Image = 0x06,
	Printer = 0x07,
	MassStorage = 0x08,
	Hub = 0x09,
	CDC_Data = 0x0A,
	SmartCard = 0x0B,
	ContentSecurity = 0x0D,
	Video = 0x0E,
	PersonalHealthcare = 0x0F,
	AVDevices = 0x10,
	BillboardDevice = 0x11,
	USBCBridge = 0x12,
	DiagDevice = 0xDC,
	WirelessController = 0xE0,
	Micellaneous = 0xEF,
	AppSpecific = 0xFE,
	VendorSpecific = 0xFF
};


enum class DeviceClassCodes : uint8_t {
	Device = (uint8_t)ClassCodes::Device,
	CDC = (uint8_t)ClassCodes::CDC_Control,
	Hub = (uint8_t)ClassCodes::Hub,
	BillboardDevice = (uint8_t)ClassCodes::BillboardDevice,
	DiagDevice = (uint8_t)ClassCodes::DiagDevice,
	Micellaneous = (uint8_t)ClassCodes::Micellaneous,
	VendorSpecific = (uint8_t)ClassCodes::VendorSpecific,
};

struct DescriptorItem {
	void* data;
	size_t len;
	uint8_t cfg_id;
	uint8_t if_num;
	DescriptorItem* next;
};

struct DeviceDesc
{
	uint8_t bLength ;
	DescType bDescriptorType;
	uint16_t USBVersion;
	DeviceClassCodes DeviceClass;
	uint8_t DeviceSubclass;
	uint8_t DeviceProtocol;
	uint8_t MaxControlPckLen;
	uint16_t VendorID;
	uint16_t ProductID;
	uint16_t DeviceVersion;
	uint8_t CompanyStringID;
	uint8_t ProductStringID;
	uint8_t SerialNumStringID;
	uint8_t ConfigurationCount;

	static void Defaults(DeviceDesc &s)
	{
		s.bLength  = sizeof(DeviceDesc);
		s.bDescriptorType =  DescType::Device;
	}

} PACKED;

struct InterfaceDesc
{
	uint8_t bLength ;
	DescType bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;

	static void Defaults(InterfaceDesc &s)
	{
		s.bLength = sizeof(InterfaceDesc);
		s.bDescriptorType = DescType::Interface;
	}

} PACKED;

struct ConfigurationDesc
{
	uint8_t bLength ;
	DescType bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	union {
	    struct {
	    	uint8_t _r0: 4;
	    	uint8_t remote_wakeup: 1;
	    	uint8_t self_powered: 1;
	    	uint8_t _r1: 1;
	    };
	    uint8_t bmAttributes;
	};
	uint8_t bMaxPower;


	static void Defaults(ConfigurationDesc &s)
	{
		s.bLength = sizeof(ConfigurationDesc);
		s.bDescriptorType = DescType::Conf;
	}

} PACKED;

struct EndpointDesc
{
	uint8_t bLength ;
	DescType bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;

	static void Defaults(EndpointDesc &s)
	{
		s.bLength = sizeof(EndpointDesc);
		s.bDescriptorType = DescType::Endpoint;
	}

} PACKED;
}

#endif /* LIB_CPP_USB_USB_MISC_HPP_ */
