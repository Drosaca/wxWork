#include "wx/wxprec.h"
#include <wx/rawbmp.h>
#include "Camera.h"
#include "camera.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MyFrame: public wxFrame
{
    public:
        MyFrame();

    private:
        void OnPaint(wxPaintEvent& event);

        wxPanel* m_board;
};

wxBitmap *gImg = NULL;
bool gImgLock = false;

MyFrame::MyFrame()
        :wxFrame(NULL, wxID_ANY, "Chess", wxDefaultPosition, wxSize(1000, 1000))
{
    m_board = new wxPanel(this, wxID_ANY);
    m_board->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);


}



void LoadImg(Frame_t *frame) {
    
   /* gImg = new wxBitmap(frame->width, frame->height, 24);
    std::cout << "load" << frame->width << std::endl;
    if(frame->imageSize == 0)
        return;
    wxNativePixelData data(*gImg);
    wxNativePixelData::Iterator p(data);
    p.Offset(data, 0, 0);

    for(int y =0; y < frame->height; y++) {
        wxNativePixelData::Iterator rowStart = p;
        for(int x = 0; x < frame->width; x++) {
            U32 index1d = frame->width * y + x; 
            U16 pixel = ((U16 *)&frame->pixels[0])[index1d];
            double intensity = pixel / pow(2, GET_PIXEL_SIZE(frame->pixelFormat));
            U8 luminance = intensity * 255;
            p.Red() = luminance;
            p.Green() = luminance;
            p.Blue() = luminance; 
        }
        p = rowStart;
        p.OffsetY(data, 1);
    }*/
    int h=100;
    int w = 100;
    gImg = new wxBitmap(100, 100, 24); 
if(!bitmap->Ok()) {
		delete bitmap;
		return NULL;
	}

	PixelData bmdata(*bitmap);
	if(bmdata==NULL) {
		wxLogDebug(wxT("getBitmap() failed"));
		delete bitmap;
		return NULL;
	}

	PixelData::Iterator dst(bmdata);

	for(int y=0; y<h; y++) {
		dst.MoveTo(bmdata, 0, y);
		for(int x=0; x<w; x++) {
			// wxBitmap contains rgb values pre-multiplied with alpha
			dst.Red()=255;
			dst.Green()=0;
			dst.Blue()=0;
			dst++;
		}
	}
    
}


void MyFrame::OnPaint(wxPaintEvent&)
{
    wxPaintDC dc(m_board);
    dc.Clear();
    std::cout << "PAINT.........." << std::endl;
    if(gImg){
        dc.DrawBitmap(*gImg, 0, 0, false);
    }
    gImgLock = false;

}


void on_frame(TeaCam_t *self, Frame_t *frame) {
    printf("%d * %d\n", frame->width, frame->height);
    printf("expected %d\n", frame->width * frame->height * 2 + 58 + 2);
    fps_counter();
    if (!gImgLock) {
        gImgLock = true;
        LoadImg(frame);
    }
    self->queue(self, frame);
}


class MyApp : public wxApp
{
    public:
    TeaCam_t *camera;
    void Backend() {
        camera = new_camera();
        run_camera(camera);
        camera->set_callback(camera, on_frame);
    }
        virtual bool OnInit()
        {
            ::wxInitAllImageHandlers();
            this->Backend();
            MyFrame* frame = new MyFrame();
            frame->Show();
            return true;
        }
};

wxIMPLEMENT_APP(MyApp);
