
// Client_MFCPP20_ModulesDoc.h : interface of the CClientMFCPP20ModulesDoc class
//


#pragma once


class CClientMFCPP20ModulesDoc : public CDocument
{
protected: // create from serialization only
	CClientMFCPP20ModulesDoc() noexcept;
	DECLARE_DYNCREATE(CClientMFCPP20ModulesDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CClientMFCPP20ModulesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
