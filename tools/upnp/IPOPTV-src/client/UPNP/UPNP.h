///////////////////////////////////////////////////////////////////////////////
// Module Name: UPNP.h
// Written By: Eric
// Purpose: ʵ�����/ɾ��UPNP�˿�ӳ��. 
//          ����UPNP������������ UPnP Device Architecture(from www.upnp.org)
///////////////////////////////////////////////////////////////////////////////

#ifndef __UPNP_PORT_MAPPING_H__
#define __UPNP_PORT_MAPPING_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
// Error Code Defines
//
// MAKE_ERROR_CODE(0) = 0x80040400
#define UPNP_ERROR_BASE		0x400
#define MAKE_ERROR_CODE(n)	MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, UPNP_ERROR_BASE + (n))

#define E_NOT_IN_LAN		MAKE_ERROR_CODE(0)		// Error: You aren't in a LAN -> no router or firewall

#define E_SEARCH_DEVICE		MAKE_ERROR_CODE(1)		// Error: Search device failed.

#define E_UNKNOWN			MAKE_ERROR_CODE(2)		// Error: This error is unknown.

#define E_INVALID_ACTION	MAKE_ERROR_CODE(401)	// Error: No action by that name at this service

#define E_INVALID_ARGS		MAKE_ERROR_CODE(402)	// Error: Could be any of the following: 
													//			not enough in args, 
													//			too many in args, 
													//			no in arg by that name, 
													//			one or more in args are of the wrong data type

#define E_ACTION_FAILED		MAKE_ERROR_CODE(501)	// Error: May be returned in current state of service prevents invoking that action.

#define E_ARG_VALUE_INVALID	MAKE_ERROR_CODE(600)	// Error: The argument value is invalid.

#define E_STR_ARG_TOO_LONG	MAKE_ERROR_CODE(605)	// Error: A string argument is too long for the device to handle properly.

#define E_INVALID_CTRL_URL	MAKE_ERROR_CODE(611)	// Error: The controlURL within the <freshness> element does not match the controlURL
													//		  of the action actually invoked(or the controlURL in the HTTP header).

#define E_CONFLICT_MAPPING	MAKE_ERROR_CODE(718)	// Error: Conflict in mapping entry.

enum PROTO_TYPE
{
	PROTO_UDP,
	PROTO_TCP
};

// Function Name: AddPortMapping
// Parameter:
//		@	ULONG:  ӳ��LAN host�ĵ�ַ
//		@	USHORT: �ⲿ�˿ں�
//		@	USHORT: �ڲ��˿ں�
//		@	PROTO_TYPE: ӳ���Э������(UDP/TCP)
//		@	LPCTSTR: ��ӳ�������
// Return Value:
//		@	HRESULT: ����ɹ�����NOERROR.
//					 ���ʧ�ܷ�������Ĵ�����Ϣ��Win32����.
// Purpose:
//		@	��Ӷ˿�ӳ��.
HRESULT AddPortMapping(ULONG ulLocalIP, USHORT usExternalPort, USHORT usInternalPort, PROTO_TYPE eProtoType, LPCTSTR pszDescription);

// Function Name: AddRandomExternalPortMapping
// Parameter:
//		@	ULONG:  ӳ��LAN host�ĵ�ַ
//		@	USHORT&: �ⲿ�˿ں�.
//		@	USHORT: �ڲ��˿ں�
//		@	PROTO_TYPE: ӳ���Э������(UDP/TCP)
//		@	LPCTSTR: ��ӳ�������
// Return Value:
//		@	HRESULT: ����ɹ�����NOERROR.
//					 ���ʧ�ܷ�������Ĵ�����Ϣ��Win32����.
// Purpose:
//		@	��Ӷ˿�ӳ��.����ͻ�ָ�����ⲿ�˿ںŲ����ã���ʹ��һ�����
//      @   �����Ķ˿ںŵķ�ΧΪ[4000, RAND_MAX]��������������usExternalPort�����С�
HRESULT AddRandomExternalPortMapping(ULONG ulLocalIP, USHORT& usExternalPort, USHORT usInternalPort, PROTO_TYPE eProtoType, LPCTSTR pszDescription);

// Function Name: AddPortMapping
// Parameter:
//		@	USHORT: �ⲿ�˿ں�
//		@	PROTO_TYPE: ӳ���Э������(UDP/TCP)
// Return Value:
//		@	HRESULT: ����ɹ�����NOERROR.
//					 ���ʧ�ܷ��ص���ErrorToString������ô�����Ϣ.
// Purpose:
//		@	ɾ�����еĶ˿�ӳ��.
HRESULT DelPortMapping(USHORT usExternalPort, PROTO_TYPE eProtoType);

LPCTSTR ErrorToString(HRESULT hr);

#endif // __UPNP_PORT_MAPPING_H__

///////////////////////////////// End of File /////////////////////////////////