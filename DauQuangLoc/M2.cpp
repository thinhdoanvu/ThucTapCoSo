#include <graphics.h>
#include <math.h>
#define ROUND(a) ((int)(a+0.5))
#define NGOAIvTRONG  1
#define TRONG        2
#define TRONGvNGOAI  3
#define NGOAI        4
#define NOT          5

//khai bao bien
int xc[100];
int yc[100];
int wx[100];
int wy[100];
int ktdiem;
int ktcuaso;
int xc_tam[100];
int yc_tam[100];
int ktdiem_tam;

void VeCanh()
{
  int i;
  //ve cac canh cua da giac
  setcolor(RED);
  setlinestyle(1,0,2);
  
  for(i=0;i<ktdiem;i++)
  {
  	// Lay toa do thu i cua canh khi click chuot
  	while(!ismouseclick(WM_LBUTTONDOWN)) { 
    		delay(500);
    	} 
    	getmouseclick(WM_LBUTTONDOWN, xc[i], yc[i]);
    // Lay toa do thu i+1 cua canh khi click chuot
    while(!ismouseclick(WM_LBUTTONDOWN)) { 
    		delay(500);
    	} 
    	getmouseclick(WM_LBUTTONDOWN, xc[i+1], yc[i+1]);
    line(xc[i],yc[i],xc[(i+1)%ktdiem],yc[(i+1)%ktdiem]);
    delay(1000);
  }
}
//chuong trinh con
void VeCuaSo()
{
  int i,j,k;
  //ve cac canh cua so cat
  setcolor(GREEN);
  setlinestyle(1,0,2);
  for(i=0;i<ktcuaso;i++)
  {
  	// Lay toa do thu i cua cua so khi click chuot
  	while(!ismouseclick(WM_LBUTTONDOWN)) { 
    		delay(500);
    	} 
    	getmouseclick(WM_LBUTTONDOWN, wx[i], wy[i]);
    // Lay toa do thu i+1 cua cua so khi click chuot
    while(!ismouseclick(WM_LBUTTONDOWN)) { 
    		delay(500);
    	} 
    	getmouseclick(WM_LBUTTONDOWN, wx[i+1], wy[i+1]);
    line(wx[i],wy[i],wx[(i+1)%ktcuaso],wy[(i+1)%ktcuaso]);
    delay(1000);
  }
  
  VeCanh();
}

//nhap thong so
void NhapDuLieu()
{
  int i;
  printf("== NHAP TOA DO DA GIAC ==");
  printf("\n->Nhap so canh cua da giac = "); //Nhap so canh cua da giac can ve
  scanf("%d",&ktdiem);
  
  printf("\n== NHAP THONG SO CUA SO CAT =="); //Nhap so canh cua cua so cat
  printf("\n->Nhap so canh cua cua so cat = ");
  scanf("%d",&ktcuaso);
}

int catTrai(int x,int x1,int x2)
{
  if(x1<x && x2>=x)
  {
    return NGOAIvTRONG;
  }
  else 
  {
    if(x1>=x && x2>=x)
    {
      return TRONG;
    }  
    else 
    {
      if(x1>=x && x2<x)
      {
        return TRONGvNGOAI;
      }
      else 
      {
        if(x1<x && x2<x)
        {
          return NGOAI;
        }
        else
        {
          return NOT;
        }
      }   
    }   
  }     
}

int catDuoi(int y,int y1,int y2)
{
    if(y1<y && y2>=y)
    {
      return NGOAIvTRONG;
    }  
    else
    {
      if(y1>=y && y2>=y)
      {
        return TRONG;
      }
      else 
      {
        if(y1>=y && y2<y)
        {
          return TRONGvNGOAI;
        }
        else 
        {
          if(y1<y && y2<y)
          { 
            return NGOAI;
          }
          else
          {
            return NOT;
          }
        } 
      }  
    } 
}

int catPhai(int x,int x1,int x2)
{
  if(x1>x && x2<=x)
  {
     return NGOAIvTRONG;
  }      
  else
  {
    if(x1<=x && x2<=x)
    {
      return TRONG;
    }
    else
    {
      if(x1<=x && x2>x)
      {
       return TRONGvNGOAI;
      }
      else
      {
        if(x1>x && x2>x)
        {
          return NGOAI;
        }
        else
        {
          return NOT;
        }
      }
    }
  }     
}

int catTren(int y,int y1,int y2)
{
  if(y1>y && y2<=y)
  {
    return NGOAIvTRONG;
  }
  else
  {
    if(y1<=y && y2<=y)
    {
      return TRONG;
    }
    else
    {
      if(y1<=y && y2>y)
      { 
        return TRONGvNGOAI;
      }
      else
      {
        if(y1>y && y2>y)
        {
          return NGOAI;
        }
        else
        {
          return NOT;
        }
      }
    }
  }
}

void xenTrai()
{
  int chieu;
  int i;
  int xwmin;
  int xa;
  int ya;
  int xb;
  int yb;
  int j;
  int xnew;
  int ynew;

  xwmin=wx[0];//dinh 1
  j=0;

  for(i=0;i<ktdiem;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=catTrai(xwmin,xa,xb);
    switch (chieu)
    {
      case NGOAIvTRONG:
      {
      	// toa do x cua diem moi cat duoc
        xnew = xwmin;
        // toa do y cua diem moi cat duoc
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);
        // gan gia tri toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case TRONG:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case TRONGvNGOAI:
      {
      	// toa do x cua diem moi cat duoc
        xnew = xwmin;
        // toa do y cua diem moi cat duoc
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);
         // gan gia tri toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case NGOAI:
      {
        break;
      }
    }
    printf("\n Chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  //gan so dinh moi sau khi xen ben trai
  ktdiem=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
 
}

void xenPhai()
{
 int chieu;
  int i;
  int xwmax;
  int xa;
  int ya;
  int xb;
  int yb;
  int j;
  int xnew;
  int ynew;

  xwmax=wx[2];;//dinh 3
  j=0;

  for(i=0;i<ktdiem;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=catPhai(xwmax,xa,xb);
    switch (chieu)
    {
      case NGOAIvTRONG:
      {
      	// toa do x cua diem moi cat
        xnew = xwmax;
        // toa do y cua diem moi cat
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);
        //gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case TRONG:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case TRONGvNGOAI:
      {
      	// toa do x cua diem moi cat
        xnew = xwmax;
        // toa do y cua diem moi cat
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);
        // gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case NGOAI:
      {
        break;
      }
    }
    printf("\n Chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  //gan so dinh moi sau khi xen ben phai
  ktdiem=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void xenDuoi()
{
  int chieu;
  int i;
  int ywmax;
  int xa;
  int ya;
  int xb;
  int yb;
  int j;
  int xnew;
  int ynew;

  ywmax=wy[2];//dinh 3
  j=0;

  for(i=0;i<ktdiem;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=catTren(ywmax,ya,yb);
    switch (chieu)
    {
      case NGOAIvTRONG:
      {
      	// toa do x cua diem moi cat
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);
        // toa do y cua diem moi cat
        ynew = ywmax;
        // gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case TRONG:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case TRONGvNGOAI:
      {
      	// toa do x cua diem moi cat
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);
        // toa do y cua diem moi cat
        ynew = ywmax;
        // gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case NGOAI:
      {
        break;
      }
    }
    printf("\n Chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  //gan so dinh moi sau khi xen ben duoi
  ktdiem=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void xenTren()
{
  int chieu;
  int i;
  int ywmin;
  int xa;
  int ya;
  int xb;
  int yb;
  int j;
  int xnew;
  int ynew;

  ywmin=wy[0];//dinh 1
  j=0;

  for(i=0;i<ktdiem;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];

    chieu=catDuoi(ywmin,ya,yb);
    
    switch (chieu)
    {
      case NGOAIvTRONG:
      {
      	// toa do x cua diem moi cat
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);
        // toa do y cua diem moi cat
        ynew = ywmin;
        // gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case TRONG:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case TRONGvNGOAI:
      {
      	// toa do x cua diem moi cat
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);
        // toa do y cua diem moi cat
        ynew = ywmin;
        // gan toa do moi
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case NGOAI:
      {
        break; // khong co diem moi duoc tao ra
      }
    }
    printf("\n Chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  //gan so dinh moi sau khi xen ben tren
  ktdiem=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}


void VeLaiSauKhiCat()
{
  int i;
  //ve cac canh cua da giac
  setcolor(YELLOW);
  setlinestyle(1,0,3);
  for(i=0;i<ktdiem;i++)
  {
    line(xc[i],yc[i],xc[(i+1)%ktdiem],yc[(i+1)%ktdiem]);
    delay(1000);
  }
}

//chuong trinh chinh
int main()
{
  
  NhapDuLieu();
  initwindow(800,750);
  VeCuaSo();
 // VeCanh();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[ktdiem]=xc[0];
  yc[ktdiem]=yc[0];
  
  xenTrai();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[ktdiem]=xc[0];
  yc[ktdiem]=yc[0];
  xenPhai();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[ktdiem]=xc[0];
  yc[ktdiem]=yc[0];
  xenDuoi();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[ktdiem]=xc[0];
  yc[ktdiem]=yc[0];
  xenTren();
  
  VeLaiSauKhiCat();

  getch();
  return 0;
}
