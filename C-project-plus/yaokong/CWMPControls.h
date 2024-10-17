// CWMPControls.h  : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPControls

class CWMPControls : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWMPControls)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x74C09E02, 0xF828, 0x11D2, { 0xA7, 0x4B, 0x0, 0xA0, 0xC9, 0x5, 0xF3, 0x6E } };
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
		InvokeHelper(0x3E, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, bstrItem);
		return result;
	}

	void play()
	{
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void stop()
	{
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void pause()
	{
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void fastForward()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void fastReverse()
	{
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	double get_currentPosition()
	{
		double result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}

	void put_currentPosition(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_currentPositionString()
	{
		CString result;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void next()
	{
		InvokeHelper(0x3A, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void previous()
	{
		InvokeHelper(0x3B, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	LPDISPATCH get_currentItem()
	{
		LPDISPATCH result;
		InvokeHelper(0x3C, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	void put_currentItem(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x3C, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_currentMarker()
	{
		long result;
		InvokeHelper(0x3D, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void put_currentMarker(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3D, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	void playItem(LPDISPATCH pIWMPMedia)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x3F, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pIWMPMedia);
	}
};
