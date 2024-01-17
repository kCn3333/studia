	/*      o--------------------------o         
		| Model ukladu slonecznego | 
		o--------------------------o
		|			   |
		|	VC++   OpenGL      |
		|			   |
		o--------------------------o
		|      Pawel  Kwiecieñ     |
		o--------------------------o
				   06/2o11
	*/
//--------------------------------------------------------------------------------------------------
#include<windows.h>                
#include<gl\gl.h>            
#include<gl\glaux.h>         
#include<math.h>             
#include<fstream>



LRESULT CALLBACK ProcessMessagefn(HWND,UINT,WPARAM,LPARAM); //windows messages recieved by this window

void SetDCPixelFormat();						// ustawienie pixeli

void CALLBACK ChangeSize(GLsizei,GLsizei);		// skalowanie okna

void RenderScene(GLfloat);						// rysowanie

int LoadGLTextures(char*, int);					// ladowanie tekstur

HDC hDC;            //device context
HGLRC hRC;          //rendering context

GLuint  texture[5];								// teksturki

//--------------------------------------------------------------------------------------------------

__stdcall WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{


    WNDCLASS wc;  
	HWND hWnd;					// uchwyt do okna
	MSG msg;					// struktura msg
	BOOL exit=FALSE;
    GLfloat xrot=0.0f;
		
	
	if(!hPrevInst)					// czy juz nie uruchomiona
	{

		wc.cbClsExtra=0;
		wc.cbWndExtra=0;
		wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hCursor=LoadCursor(NULL,IDC_ARROW);
		wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
		wc.hInstance=hInst;
		wc.lpfnWndProc=(WNDPROC)ProcessMessagefn;
		wc.lpszClassName="MyClass";
		wc.lpszMenuName=NULL;
		wc.style=0;


		if(!RegisterClass(&wc))		// rejestracja klasy
		{

			MessageBox(0,"Cannot Register Class","kCn",MB_OK);
			return FALSE;
		}

	}
									// tworzenie okna
	hWnd=CreateWindow("MyClass","Uklad Sloneczny  - Pawe³ Kwiecieñ -",WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,10,10,800,640,NULL,NULL,hInst,NULL);
		
	if(!hWnd)
	{

		MessageBox(0,"cannot create window","kCn",MB_OK);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);					// pokaz okno
												// ladowanie tekstur
	LoadGLTextures("data/slonce.bmp", 0);
	LoadGLTextures("data/merkury.bmp", 1);
	LoadGLTextures("data/wenus.bmp", 2);	
	LoadGLTextures("data/ziemia.bmp", 3);
	LoadGLTextures("data/mars.bmp", 4);

	while(!exit)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message==WM_QUIT)
			{
				exit=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
											// jesli wszystko ok, rysuj
		else
		{
			RenderScene(xrot);
			xrot++;
			if(xrot>360.0f)
				xrot=0.0f;
		}
	}

return(msg.wParam);
}

LRESULT CALLBACK ProcessMessagefn(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	//This message is sent whenever a window is created
	case WM_CREATE:
		hDC=GetDC(hWnd);			//creating device context
		SetDCPixelFormat();			//setting the pixel format for device context
		hRC=wglCreateContext(hDC);  //creating the rendering context
		wglMakeCurrent(hDC,hRC);    //making the values as current
		break;
	//This message is sent whenever a window is destroyed
	case WM_DESTROY:
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);  //deleting the rendering context
		ReleaseDC(hWnd,hDC);     //releasing the device context
		PostQuitMessage(0);
		break;
	//This message is sent wnenever the size of window is changed
	case WM_SIZE:
		ChangeSize(LOWORD(lParam),HIWORD(lParam));
		break;
	//default execution for all the other window messages
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return(0);
}

//--------------------------------------------------------------------------------------------------
void SetDCPixelFormat()
{

    int index;

	PIXELFORMATDESCRIPTOR pfd;
									// wypelnianie struktury pfd
	pfd.cColorBits=24;
	pfd.cDepthBits=32;
	pfd.dwFlags=(PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER);
	pfd.iLayerType=PFD_MAIN_PLANE;
	pfd.iPixelType=PFD_TYPE_RGBA;
	pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion=1;

	index=ChoosePixelFormat(hDC,&pfd);
	SetPixelFormat(hDC,index,&pfd);

}
//--------------------------------------------------------------------------------------------------

void CALLBACK ChangeSize(GLsizei w,GLsizei h)		// zmiana wielkosci okna
{
    GLfloat faspect;

	if(h==0)
		h=1;

	glViewport(0,0,w,h);
	faspect=w/(GLfloat)h;   // ratio

	glMatrixMode(GL_PROJECTION);   

    glLoadIdentity();

	gluPerspective(45,faspect,1.0f,525.0f);
	
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

}
//--------------------------------------------------------------------------------------------------

AUX_RGBImageRec *LoadBMP(char* filename)		// odczyt tekstury z pliku
{
    FILE* file=NULL;

    if (!filename)
    {
        return NULL;
    }

    file=fopen( filename, "r" );
    if( file )
    {
        fclose( file );
        return auxDIBImageLoad( filename );
    }

    return NULL;
}
//--------------------------------------------------------------------------------------------------

int LoadGLTextures(char* file, int n)			// ladowanie tekstury
{
    int status=FALSE;
    AUX_RGBImageRec *TextureImage[1];

    memset(TextureImage,0,sizeof(void *)*1);
    if (TextureImage[0]=LoadBMP(file))
    {
        status=TRUE;
        glGenTextures(1, &texture[n]);
        glBindTexture(GL_TEXTURE_2D, texture[n]);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 
                          GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }

    if (TextureImage[0])
    {
        if (TextureImage[0]->data)
        {
            free(TextureImage[0]->data);
        }
        free(TextureImage[0]);
    }

    return status;
}
//--------------------------------------------------------------------------------------------------

void RenderScene(GLfloat xr)							// rysowanie
{

	for (int yy=0;yy<10000000;yy++){ }					// pusta petla, zeby opoznic krazenie planet ;)

	GLfloat p[]={50.0f,50.0f,50.0f,1.0f};				// tablice ustawien swiatla
    GLfloat q[]={0.0f,0.0f,0.0f,1.0f}; 

	glClearColor(0.0f,0.0f,0.0f,1.0f);					// kolor tla

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	// czysci bufor koloru

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);								// wlacza oswietlanie

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT0,GL_POSITION,p);					// ustawia swiatlo
   //glLightfv(GL_LIGHT0,GL_POSITION,q);

   glEnable(GL_LIGHT0);									// wlacza swiatlo

   glTranslatef(0.0f,0.0f,-300.0f);						

       // ------ Slonce -------
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

   glBindTexture(GL_TEXTURE_2D, texture[0]);
   auxSolidSphere(20.0f);
   glDisable(GL_TEXTURE_2D);
   glLightfv(GL_LIGHT0,GL_POSITION,p);
   
       // ------ Merkury -------
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

   glBindTexture(GL_TEXTURE_2D, texture[2]);
   glPushMatrix();
   glRotatef(20,0.0f,0.0f,1.0f);
   glRotatef(xr+40,0.0f,1.0f,0.0f);
   glTranslatef(90.0f,0.0f,0.0f);
   glColor3f(1.0f,0.0f,0.0f);
   
   auxSolidSphere(6.0f);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

        // ------ Wenus -------
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
  
   glBindTexture(GL_TEXTURE_2D, texture[1]);
   glPushMatrix();
   glRotatef(15,0.0f,0.0f,1);
   glRotatef(xr+75,0.0f,1.0f,0.0f);
   glTranslatef(45.0f,0.0f,0.0f);

   auxSolidSphere(4.0f);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);


    // ------ Ziemia -------
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

   glBindTexture(GL_TEXTURE_2D, texture[3]);
   glPushMatrix();
   glRotatef(10.0,0.0f,0.0f,1.0f);
   glRotatef(xr+20,0.0f,1.0f,0.0f);
   glTranslatef(150.0f,0.0f,0.0f);
   
   auxSolidSphere(5.0f);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   
      // ------ Mars -------  
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

   glBindTexture(GL_TEXTURE_2D, texture[4]);
   glPushMatrix();
   glRotatef(15,0.0f,0.0f,1.0f);
   glRotatef(xr+5,0.0f,1.0f,0.0f);
   glTranslatef(200.0f,0.0f,0.0f);
   glColor3f(0.5f,0.4f,0.2f);
   
   auxSolidSphere(4.5f);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   SwapBuffers(hDC); // przelacza bufor

   glFlush();   
}
