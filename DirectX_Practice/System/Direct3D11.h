#pragma once

#include "DirectXIncLib.h"

class Direct3D11 {
public:
    Direct3D11();
    ~Direct3D11();
    HRESULT init(const HWND& hWnd);
    void clear();
    HRESULT present();
    ID3D11Device* device() const;
    ID3D11DeviceContext* deviceContext() const;

    static ID3D11Device* mDevice;
    static ID3D11DeviceContext* mDeviceContext;
    static ID3D11RasterizerState* mRasterizerState; //‘O–Ê—p
    static ID3D11RasterizerState* mRasterizerStateBack; //”w–Ê—p

private:
    HWND mhWnd;
    IDXGISwapChain* mSwapChain;
    ID3D11RenderTargetView* mRenderTargetView;
    ID3D11DepthStencilView* mDepthStencilView;
    ID3D11Texture2D* mDepthStencil;
    ID3D11DepthStencilState* mDepthStencilState;
    ID3D11BlendState* mBlendState;
};

