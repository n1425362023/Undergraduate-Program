// CWMPMedia.h  : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPMedia

class CWMPMedia : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWMPMedia)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x94D55E95, 0x3FAC, 0x11D3, { 0xB1, 0x55, 0x0, 0xC0, 0x4F, 0x79, 0xFA, 0xA6 } };
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

	BOOL get_isIdentical(LPDISPATCH pIWMPMedia)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x2FB, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, pIWMPMedia);
		return result;
	}

	CString get_sourceURL()
	{
		CString result;
		InvokeHelper(0x2EF, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	CString get_name()
	{
		CString result;
		InvokeHelper(0x2FC, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2FC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_imageSourceWidth()
	{
		long result;
		InvokeHelper(0x2F0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	long get_imageSourceHeight()
	{
		long result;
		InvokeHelper(0x2F1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	long get_markerCount()
	{
		long result;
		InvokeHelper(0x2F2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	double getMarkerTime(long MarkerNum)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2F3, DISPATCH_METHOD, VT_R8, (void*)&result, parms, MarkerNum);
		return result;
	}

	CString getMarkerName(long MarkerNum)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2F4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, MarkerNum);
		return result;
	}

	double get_duration()
	{
		double result;
		InvokeHelper(0x2F5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}

	CString get_durationString()
	{
		CString result;
		InvokeHelper(0x2F6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	long get_attributeCount()
	{
		long result;
		InvokeHelper(0x2F7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	CString getAttributeName(long lIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2F8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lIndex);
		return result;
	}

	CString getItemInfo(LPCTSTR bstrItemName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2F9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrItemName);
		return result;
	}

	void setItemInfo(LPCTSTR bstrItemName, LPCTSTR bstrVal)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x2FA, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrItemName, bstrVal);
	}

	CString getItemInfoByAtom(long lAtom)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2FD, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lAtom);
		return result;
	}

	BOOL isMemberOf(LPDISPATCH pPlaylist)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x2FE, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pPlaylist);
		return result;
	}

	BOOL isReadOnlyItem(LPCTSTR bstrItemName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2FF, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstrItemName);
		return result;
	}



};
