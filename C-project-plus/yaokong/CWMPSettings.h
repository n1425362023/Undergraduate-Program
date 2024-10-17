// CWMPSettings.h  : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPSettings

class CWMPSettings : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWMPSettings)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x9104D1AB, 0x80C9, 0x4FED, { 0xAB, 0xF0, 0x2E, 0x64, 0x17, 0xA6, 0xDF, 0x14 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID,
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
	}

// 特性
public:

// 操作
public:

	BOOL get_isAvailable(LPCTSTR bstrItem)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, bstrItem);
		return result;
	}

	BOOL get_autoStart()
	{
		BOOL result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_autoStart(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_baseURL()
	{
		CString result;
		InvokeHelper(0x6C, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_baseURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6C, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_defaultFrame()
	{
		CString result;
		InvokeHelper(0x6D, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_defaultFrame(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6D, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_invokeURLs()
	{
		BOOL result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_invokeURLs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_mute()
	{
		BOOL result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_mute(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_playCount()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_playCount(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	double get_rate()
	{
		double result;
		InvokeHelper(0x6A, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}

	void put_rate(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6A, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_balance()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_balance(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_volume()
	{
		long result;
		InvokeHelper(0x6B, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_volume(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6B, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL getMode(LPCTSTR bstrMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6E, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstrMode);
		return result;
	}

	void setMode(LPCTSTR bstrMode, BOOL varfMode)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x6F, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrMode, varfMode);
	}

	BOOL get_enableErrorDialogs()
	{
		BOOL result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_enableErrorDialogs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}



};
