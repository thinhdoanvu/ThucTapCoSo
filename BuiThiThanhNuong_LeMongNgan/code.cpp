#include <graphics.h>
#include <math.h>
#define ROUND(a) ((int)(a+0.5))

#define OUT2IN  1 //tra ve gia tri 1 trong truong hop chieu tu ngoai vao trong
#define INSIDE      2 //tra ve gia tri 2 trong truong hop nam trong cua so cat
#define IN2OUT  3 //tra ve gia tri 3 trong truong hop chieu tu trong ra ngoai
#define OUTSIDE     4 //tra ve gia tri 4 trong truong hop nam ngoai cua so cat
#define INVALID 5 //tra ve gia tri 5 trong truong hop khong co gia tri

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


//ve 
void draw_object()
{
  int i;
  //ve cac canh cua da giac can xen
  setcolor(RED); //ve mau do
  for(i=0;i<pointsize;i++)
  {
    line(xc[i],yc[i],xc[(i+1)%pointsize],yc[(i+1)%pointsize]);
    delay(1000);
  }
  //ve cac canh cua so cat
  setcolor(BLUE);//ve mau xanh
  for(i=0;i<windowsize;i++)
  {
    line(wx[i],wy[i],wx[(i+1)%windowsize],wy[(i+1)%windowsize]);
    delay(1000);
  }
}

//nhap thong so
void nhapdulieu()
{
  int i;
  printf("Nhap so canh cua da giac = "); //nhap so canh cua da giac
  scanf("%d",&pointsize);
  
  for (i=0;i<pointsize;i++)
  {
    printf("Toa do x cho canh %d = ",i); //nhap toa do diem x cua da giac
    scanf("%d",&xc[i]);
    printf("Toa do y cho canh %d = ",i);//nhap toa do diem y cua da giac
    scanf("%d",&yc[i]);
  }

  printf("Nhap so canh cua cua so clipping = ");//nhap so canh cua cua so cat
  scanf("%d",&windowsize);
  
  for (i=0;i<windowsize;i++)
  {
    printf("Toa do x cho canh window %d = ",i);//nhap toa do diem x cua cua so cat
    scanf("%d",&wx[i]);
    printf("Toa do y cho canh window %d = ",i);//nhap toa do diem y cua cua so cat
    scanf("%d",&wy[i]);
  }
}

//xac dinh chieu doi voi truong hop xen canh ben trai
int clipLeft(int x,int x1,int x2)
{
  if(x1<x && x2>=x)
  {
    return OUT2IN; //tra ve gia tri chieu tu ngoai vao trong 
  }
  else 
  {
    if(x1>=x && x2>=x)
    {
      return INSIDE; //tra ve gia tri chieu nam trong cua so cat
    }  
    else 
    {
      if(x1>=x && x2<x)
      {
        return IN2OUT;//tra ve gia tri chieu tu trong  ra ngoai
      }
      else 
      {
        if(x1<x && x2<x)
        {
          return OUTSIDE; //tra ve gia tri chieu nam ngoai cua so cat
        }
        else
        {
          return INVALID; //tra ve khong gia tri
        }
      }   
    }   
  }     
}
//xac dinh chieu doi voi truong hop xen canh ben duoi
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
//xac dinh chieu doi voi truong hop xen canh ben phai
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
//xac dinh chieu doi voi truong hop xen canh ben tren
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
//xen canh ben trai
void leftclipper()
{
  int chieu, i, xwmin, xa, ya, xb, yb, j=0, xnew, ynew;
   xwmin=wx[0];//dinh 1
   for(i=0;i<pointsize;i++)
  {//gan gia tri
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    chieu=clipLeft(xwmin,xa,xb);//xac dinh chieu 
    switch (chieu)
    {
      case OUT2IN://truong hop ngoai vao trong
      {
        xnew = xwmin;//toa do x
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);//toa do y
        //gan gia tri
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE://truong hop nam trong cua so cat
      {
        xnew = xb;//toa do x
        ynew = yb;//toa do y 
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        break;
      }  
      case IN2OUT://truong hop chieu tu trong ra ngoai
      {
        xnew = xwmin;//toa do x
        ynew = ya + (float)(yb-ya)*(float)(xwmin-xa)/(float)(xb-xa);//toa do y
        xc_tam[j]=xnew; //gan gia tri x
        yc_tam[j]=ynew;//gan gia tri y
        j++;
        break;
      }     
      case OUTSIDE://truong hop nam ngoai cua so cat
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
 int chieu, i, xwmax, xa, ya, xb, yb, j=0, xnew, ynew;
  xwmax=wx[2];;//dinh 3
  //gan gia tri
  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    chieu=clipRight(xwmax,xa,xb);//xac dinh chieu cua truong hop xen ben phai
    switch (chieu)
    {
      case OUT2IN://TH ngoai vao trong
      {
        xnew = xwmax;//toa do x
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);//toa do y
        //gan gia tri
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE://TH nam trong cua so cat
      {
        xnew = xb;//toa do x
        ynew = yb;//toa do y
        xc_tam[j]=xnew;//gan gia tri cho toa do x
        yc_tam[j]=ynew;//gan gia tri cho toa do y
        j++;
        break;
      }  
      case IN2OUT://TH chieu tu trong ra ngoai
      {
        xnew = xwmax;//xac dinh toa do x
        ynew = ya + (float)(yb-ya)*(float)(xwmax-xa)/(float)(xb-xa);//xac dinh toa do y
        xc_tam[j]=xnew;//gan gia tri toa do x
        yc_tam[j]=ynew;//gan gia tri toa do y
        j++;
        break;
      }     
      case OUTSIDE://TH nam ngoai cua so cat
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
  //gan so dinh moi sau khi rightclipper
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void bottomclipper()
{
  int chieu, i, ywmax, xa, ya, xb, yb, j=0, xnew, ynew;
  ywmax=wy[2];//dinh 3
	//gan gia tri cho diem
  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];
    
    chieu=clipTop(ywmax,ya,yb);//xac dinh chieu 
    switch (chieu)
    {
      case OUT2IN://TH chieu tu ngoai vao trong
      {
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);// toa do x
        ynew = ywmax;//toa do y
        //gan gia tri toa do
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE://TH nam trong cua so cat
      {
        xnew = xb;//toa do x
        ynew = yb;//toa do y
        xc_tam[j]=xnew;//gan toa do x
        yc_tam[j]=ynew;//gan toa do y
        j++;
        break;
      }  
      case IN2OUT://TH chieu tu trong ra ngoai
      {
        xnew = xa + (float)(ywmax-ya)*(xb-xa)/(yb-ya);//toa do x
        ynew = ywmax;//toa do y
        xc_tam[j]=xnew;//gan gia tri toa do x
        yc_tam[j]=ynew;//gan gia tri toa do y
        j++;
        break;
      }     
      case OUTSIDE://TH ngoai cua so
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
  //gan so dinh moi sau khi rightclipper
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

void topclipper()
{
  int chieu, i, ywmin, xa, ya, xb, yb, j=0, xnew, ynew;
  ywmin=wy[0];//dinh 1
	//gan gia tri
  for(i=0;i<pointsize;i++)
  {
    xa=xc[i];
    ya=yc[i];
    xb=xc[i+1];
    yb=yc[i+1];

    chieu=clipBottom(ywmin,ya,yb);//xac dinh chieu trong truong hop xen canh ben duoi
    
    switch (chieu)
    {
      case OUT2IN://TH chieu tu ngoai vao trong
      {
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);//toa do x
        ynew = ywmin;//toa do y
        //gan gia tri toa do
        xc_tam[j]=xnew;
        yc_tam[j]=ynew;
        j++;
        xc_tam[j]=xb;
        yc_tam[j]=yb;
        j++;
        break;
      }
      case INSIDE://TH nam trong cua so cat
      {
        xnew = xb;//toa do x
        ynew = yb;//toa do y
        xc_tam[j]=xnew;//gan gia tri toa do x
        yc_tam[j]=ynew;//gan gia tri toa do y
        j++;
        break;
      }  
      case IN2OUT://TH chieu tu trong ra ngoai
      {
        xnew = xa + (float)(ywmin-ya)*(xb-xa)/(yb-ya);//toa do x
        ynew = ywmin;//toa do y
        xc_tam[j]=xnew;//gan gia tri toa do x
        yc_tam[j]=ynew;//gan gia tri toa do y
        j++;
        break;
      }     
      case OUTSIDE://TH ngoai cua so cat
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
  //gan so dinh moi sau khi rightclipper
  pointsize=j;

  for(i=0;i<j;i++)
  {
    printf("(%d,%d); ",xc[i],yc[i]);
  }
  printf("\n");
}

//ve da giac sau khi xen 
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
  xc[pointsize]=xc[0];
  yc[pointsize]=yc[0];
  
  leftclipper();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[pointsize]=xc[0];
  yc[pointsize]=yc[0];
  rightclipper();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[pointsize]=xc[0];
  yc[pointsize]=yc[0];
  bottomclipper();
  //gan them 1 dinh o cuoi cung chinh la dinh xuat phat
  xc[pointsize]=xc[0];
  yc[pointsize]=yc[0];
  topclipper(); 
  
  draw_object_afterclip();

  getch();
  return 0;
}
