#include <graphics.h>
#include <math.h>
#define ROUND(a) ((int)(a+0.5))

#define OUT2IN  1
#define INSIDE      2
#define IN2OUT  3
#define OUTSIDE     4
#define INVALID 5

//khai bao bien
int xc[100];
int yc[100];
int wx[100];
int wy[100];
int pointsize;
int windowsize;
int xc_tam[100];
int yc_tam[100];
int pointsize_tam;


//chuong trinh con
void draw_object()
{
  int i;
  //ve cac canh cua da giac
  setcolor(RED);
  for(i=0;i<pointsize;i++)
  {
    line(xc[i],yc[i],xc[(i+1)%pointsize],yc[(i+1)%pointsize]);
    delay(1000);
  }
  //ve cac canh cua so clipping
  setcolor(BLUE);
  for(i=0;i<windowsize;i++)
  {
    line(wx[i],wy[i],wx[(i+1)%windowsize],wy[(i+1)%windowsize]);
    delay(1000);
  }
}

//nhap thong so
void nhapdulieu()
{
  int i;//nhap i la 1 so nguyen.

  printf("Nhap so canh cua da giac = ");//nhap so canh cua các da giác
  scanf("%d",&pointsize);
  
  for (i=0;i<pointsize;i++)//cho i chay tu 0 cho den khi i nho hon kich thuoc cua diem thi tang i them 1 don vi
  {
    printf("Toa do x cho canh %d = ",i);//nhap thu tu các toa do x cho cac canh 
    scanf("%d",&xc[i]);
    printf("Toa do y cho canh %d = ",i);//nhap thu tu cac toa do y cho cac canh
    scanf("%d",&yc[i]);
  }

  printf("Nhap so canh cua cua so clipping = ");//nhap so canh cua cua so cat
  scanf("%d",&windowsize);
  
  for (i=0;i<windowsize;i++)//cho vong lap chay tu i=0 cho den khi i nho hon kich thuoc cua so cat thi tang i len 1 don vi
  {
    printf("Toa do x cho canh window %d = ",i);//nhap toa do x cho canh cua cua so cat
    scanf("%d",&wx[i]);
    printf("Toa do y cho canh window %d = ",i);//nhap toa do y caho canh cua cua so cat
    scanf("%d",&wy[i]);
  }
}

int clipLeft(int x,int x1,int x2)
{
  if(x1<x && x2>=x)
  {
    return OUT2IN;
  }
  else 
  {
    if(x1>=x && x2>=x)
    {
      return INSIDE;
    }  
    else 
    {
      if(x1>=x && x2<x)
      {
        return IN2OUT;
      }
      else 
      {
        if(x1<x && x2<x)
        {
          return OUTSIDE;
        }
        else
        {
          return INVALID;
        }
      }   
    }   
  }     
}

int clipBottom(int y,int y1,int y2)
{
    if(y1<y && y2>=y)
    {
      return OUT2IN;
    }  
    else
    {
      if(y1>=y && y2>=y)
      {
        return INSIDE;
      }
      else 
      {
        if(y1>=y && y2<y)
        {
          return IN2OUT;
        }
        else 
        {
          if(y1<y && y2<y)
          { 
            return OUTSIDE;
          }
          else
          {
            return INVALID;
          }
        } 
      }  
    } 
}

int clipRight(int x,int x1,int x2)
{
  if(x1>x && x2<=x)
  {
     return OUT2IN;
  }      
  else
  {
    if(x1<=x && x2<=x)
    {
      return INSIDE;
    }
    else
    {
      if(x1<=x && x2>x)
      {
       return IN2OUT;
      }
      else
      {
        if(x1>x && x2>x)
        {
          return OUTSIDE;
        }
        else
        {
          return INVALID;
        }
      }
    }
  }     
}

int clipTop(int y,int y1,int y2)
{
  if(y1>y && y2<=y)
  {
    return OUT2IN;
  }
  else
  {
    if(y1<=y && y2<=y)
    {
      return INSIDE;
    }
    else
    {
      if(y1<=y && y2>y)
      { 
        return IN2OUT;
      }
      else
      {
        if(y1>y && y2>y)
        {
          return OUTSIDE;
        }
        else
        {
          return INVALID;
        }
      }
    }
  }
}

void leftclipper()
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

  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=clipLeft(xwmin,xa,xb);
    switch (chieu)
    {
      case OUT2IN:
      {
        xnew = xwmin;
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case IN2OUT:
      {
        xnew = xwmin;
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case OUTSIDE:
      {
        break;
      }
    }
    printf("\n chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  //gan so dinh moi sau khi leftclipper
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
 
}

void rightclipper()
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

  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=clipRight(xwmax,xa,xb);
    switch (chieu)
    {
      case OUT2IN:
      {
        xnew = xwmax;
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case IN2OUT:
      {
        xnew = xwmax;
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case OUTSIDE:
      {
        break;
      }
    }
    printf("\n chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void bottomclipper()
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

  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=clipTop(ywmax,ya,yb);
    switch (chieu)
    {
      case OUT2IN:
      {
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);
        ynew = ywmax;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE:
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case IN2OUT:
      {
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);
        ynew = ywmax;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case OUTSIDE:
      {
        break;
      }
    }
    printf("\n chieu = %d\n",chieu);
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
  
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void topclipper()
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

  ywmin=wy[0];//dinh 1.
  j=0;

  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];

    chieu=clipBottom(ywmin,ya,yb);
    
    switch (chieu)
    {
      case OUT2IN://doan thang di theo huong tu ngoai vao trong
      {
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);
        ynew = ywmin;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE://doan thang nam hoan toan ben trong cua so cat
      {
        xnew = xb;
        ynew = yb;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case IN2OUT://doan thang di theo huong tu trong ra ngoai
      {
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);
        ynew = ywmin;
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }     
      case OUTSIDE://doan thang nam hoan toan ben ngoai cua so cat
      {
        break;
      }
    }
    printf("\n chieu = %d\n",chieu);//sau khi xac dinh xong thi in ra chieu cua doan thang
  }

  //gan lai danh sach canh moi
  for(i=0;i<j;i++)
  {
    xc[i]=xc_tam[i];
    yc[i]=yc_tam[i];
  } 
 
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}


void draw_object_afterclip()
{
  int i;
  //ve cac canh cua da giac
  setcolor(YELLOW);
  setlinestyle(1,0,1);
  for(i=0;i<pointsize;i++)
  {
    line(xc[i],yc[i],xc[(i+1)%pointsize],yc[(i+1)%pointsize]);
    delay(1000);
  }
}


//chuong trinh chinh
int main()
{
  nhapdulieu();
  initwindow(800,800);
  draw_object();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
 // xc[pointsize]=xc[0];
 // yc[pointsize]=yc[0];
 // 
  //leftclipper();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
 // xc[pointsize]=xc[0];
 // yc[pointsize]=yc[0];
 // rightclipper();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[pointsize]=xc[0];
  yc[pointsize]=yc[0];
  bottomclipper();
 //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  //xc[pointsize]=xc[0];
  //yc[pointsize]=yc[0];
  //topclipper();
  
  
  draw_object_afterclip();

  getch();
  return 0;
}
