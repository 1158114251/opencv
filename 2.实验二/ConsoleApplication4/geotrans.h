//Download by http://www.NewXing.com
// GeoTransView.h : interface of the CGeoTransView class
//
/////////////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_GEOTRANSVIEW_H__CC49AA74_C456_46BD_A29D_D57375DABA71__INCLUDED_)
#define AFX_GEOTRANSVIEW_H__CC49AA74_C456_46BD_A29D_D57375DABA71__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
 
class CGeoTransView : public CScrollView
{
protected: // create from serialization only
    CGeoTransView();
    DECLARE_DYNCREATE(CGeoTransView)
 
// Attributes
public:
    CGeoTransDoc * GetDocument();
 
// Operations
public:
 
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGeoTransView)
    public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
    //}}AFX_VIRTUAL
 
// Implementation
public:
    virtual ~CGeoTransView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
 
protected:
 
// Generated message map functions
protected:
    //{{AFX_MSG(CGeoTransView)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam);  // user message
    afx_msg void OnGeomRota();
    afx_msg void OnGeomMirh();
    afx_msg void OnGeomMirv();
    afx_msg void OnGeomTran();
    afx_msg void OnGeomTrpo();
    afx_msg void OnGeomZoom();
    afx_msg void OnMenuitem32773();
    afx_msg void OnToPolar();
    afx_msg void OnToCartesian();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
 
#ifndef _DEBUG  // debug version in GeoTransView.cpp
inline CGeoTransDoc* CGeoTransView::GetDocument()
   { return (CGeoTransDoc*)m_pDocument; }
#endif
 
/////////////////////////////////////////////////////////////////////////////
 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
 
#endif // !defined(AFX_GEOTRANSVIEW_H__CC49AA74_C456_46BD_A29D_D57375DABA71__INCLUDED_)
