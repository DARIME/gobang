/*********************************/
/*           ���������          */
/*           ��һ������          */
/*********************************/

//���������ͨ��easyxʵ�ֻ�ͼ�����������������¡�
//�������Ϊ�������㷨��ͨ����ά�������������̼�¼��Ϣ��ͨ���㷨ʵ����Ӯ���˻���
//�������⣬С���ڽ�����������˺ܴ󹦷򣬸����������ǽ��ܡ�
#include<graphics.h>     //c���Ի�ͼͷ�ļ�
#include<conio.h>
#pragma comment(lib,"Winmm.lib")  //���������ļ���Ҫ

int qipan[19][19]={0};         //��ά�������������̣���ʼ��Ϊ0������û�����ӣ�����ʱ��Ӧλ�ü�¼1��������ӣ�2��������ӣ�
int jilu[4]={0};               //������Ϣ����ʱ��¼�����ڻ���
IMAGE heizi,baizi,kongbai;     // ���� IMAGE ���󣬼���ͼƬ��Ϣ
int judge (int qipan[][19],int );//�ж���Ӯ��������������ڴ��ݸ�chongzhi�����ж�ˢ��������һ��ͼƬ
void chongzhi (int);           //ˢ�������������ж�ˢ������ʾ�˻����滹��˫�˽��档
void doubleplayer(void);	   //˫����Ϸ����
void singleplayer(void);       //������Ϸ����
int score (int m,int n,int k); //�Ƿֺ������˻��㷨�ĺ��ģ��������̿հ�λ�õķ�ֵ
void ai (void);                //�˻��������������п�������λ���з�ֵ��������
int main()
{
	mciSendString("open luozisheng.mp3 alias mymusic", NULL, 0, NULL);//���������ļ�
	initgraph (760,650);       //���û��������ڻ�ͼ  ����ͼƬ
	IMAGE img;                 //IMAGE ����
	loadimage(&heizi,"����.jpg");  //װ��ͼƬ
	loadimage(&baizi,"����.jpg");
	loadimage(&kongbai,"�հ�.jpg");
	loadimage(&img, "���������.jpg");	// ��ȡͼƬ�� img ������
	putimage(0, 0, &img);      //��0,0����λ�÷���ͼƬ
	MOUSEMSG n;                //����������
	while(1)
	{
	n=GetMouseMsg();           //��ȡ�����Ϣ
	if(n.uMsg==WM_LBUTTONDOWN) //��������£�����λ������ָ����Χ��ʱ��ִ�ж�Ӧ���룬�ȴﵽ�ˡ���ť����Ч��
	{
		if(n.x>=250&&n.x<=510&&n.y>=300&&n.y<=360)//ѡ������Ϸ
		{
			chongzhi(1);
			singleplayer();
		}
		if(n.x>=250&&n.x<=510&&n.y>=435&&n.y<=500)//ѡ��˫����Ϸ
		{
			chongzhi(2);
			doubleplayer();
		}
	}
	}
	_getch ();
	closegraph();
	return 0;
}

int judge(int qipan[][19],int o )//�ж���Ӯ������ɨ��qipan������ÿһ���㣬�����ӵĵ㿪ʼ���ֱ������ӵ����£��£����£����ĸ�����ʼ�������ĸ�������������ͬ�����֣�1��2�ֱ����ڰף������ɹ���
{
	for(int i=0;i<=18;i++)
		for(int j=0;j<=18;j++)
		{
			if (qipan[i][j]==1)
			{
				if(qipan[i][j+1]==1)
				{	if(qipan[i][j+2]==1)
						if(qipan[i][j+3]==1)
							if(qipan[i][j+4]==1)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}

				}
				if(qipan[i+1][j]==1)
				{	if(qipan[i+2][j]==1)
						if(qipan[i+3][j]==1)
							if(qipan[i+4][j]==1)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
								{chongzhi(o);
								return 1;}}
				}
				if(qipan[i+1][j+1]==1)
				{	if(qipan[i+2][j+2]==1)
						if(qipan[i+3][j+3]==1)
							if(qipan[i+4][j+4]==1)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"),MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
				if(qipan[i-1][j+1]==1)
				{	if(qipan[i-2][j+2]==1)
						if(qipan[i-3][j+3]==1)
							if(qipan[i-4][j+4]==1)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
			}

			else if(qipan[i][j]==2)
			{
				if(qipan[i][j+1]==2)
				{	if(qipan[i][j+2]==2)
						if(qipan[i][j+3]==2)
							if(qipan[i][j+4]==2)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
				if(qipan[i+1][j]==2)
				{	if(qipan[i+2][j]==2)
						if(qipan[i+3][j]==2)
							if(qipan[i+4][j]==2)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
				if(qipan[i+1][j+1]==2)
				{	if(qipan[i+2][j+2]==2)
						if(qipan[i+3][j+3]==2)
							if(qipan[i+4][j+4]==2)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
				if(qipan[i-1][j+1]==2)
				{	if(qipan[i-2][j+2]==2)
						if(qipan[i-3][j+3]==2)
							if(qipan[i-4][j+4]==2)
							{HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
							{chongzhi(o);
							return 1;}}
				}
			}
			else continue;
		}
return 0;
}
void chongzhi (int w)   //ˢ������
{
	if(w==2)            //��ȡ2����Ϣʱ�������˫����ϷͼƬ��1ʱ���ص�����ϷͼƬ
	{
		IMAGE img;	// ���� IMAGE ����
		loadimage(&img, "˫�˶�ս.jpg");	// ��ȡͼƬ�� img ������
		putimage(0, 0, &img);
	}
	else
	{
		IMAGE img;	// ���� IMAGE ����
		loadimage(&img, "�˻���ս.jpg");	// ��ȡͼƬ�� img ������
		putimage(0, 0, &img);
	}
	for(int a=50;a<=590;a+=30)    //��������
	{
	setlinecolor(RGB(93,42,11));     //���û��ߵ���ɫ
	line(a,50,a,590);				//���ߴ� ��a��50������a��590��
	line(50,a,590,a);
		for(int i=0;i<=18;i++)
		for(int j=0;j<=18;j++)
			qipan[i][j]=0;          //���ú���������ȫ������
	}
}
void doubleplayer ()          //˫�˶�ս����
{
	MOUSEMSG m;
	m=GetMouseMsg();
	int b=2;                 //����ͨ����ż��ʵ�ֺ��Ӱ��ֵĸı�
	int xx,yy;               //�н���������ڰѺ����������������������໥ת����
		while(1)
	{
		m=GetMouseMsg();    //��ȡ�����Ϣ
		switch(m.uMsg)
	{
		case WM_LBUTTONDOWN:  //������������ʱ
		{
		if(b%2==0)
		{
			if(m.x>=644&&m.x<=730&&m.y>=304&&m.y<=340)   // ���ڴ˷�Χ�ڣ����л��������Ӧͼ�ϵĻ��尴ť
			{
				if(qipan[xx][yy]==0)
				{
					HWND wnd = GetHWnd();
					if (MessageBox(wnd, _T("������û������֪������Ĵ�����鷳��!!!"), _T("�Բ�!"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK);
				}
				else
				{
					putimage(xx*30+35,yy*30+35,&kongbai);  //��һ�ſ�ͼƬ�������ӣ�Ч�����ǻ����Ч��
					qipan[xx][yy]=0;                       //�����������ϴ˵�����
					b--;                                   //����һ��BUG��ÿ��һ���壬���ӵ���ɫ����䣡������֮�£�ֻ�������ˣ���֮�ǽ���ˣ���Ȼ��֪�����b--��Ϊɶ��
				}
			}
			if(m.x>=680&&m.x<=733&&m.y>=8&&m.y<=61)       //����
			{
				main();
			}
			if(m.x>=644&&m.x<=730&&m.y>=241&&m.y<=275)   //��ʼ����ˢ��
			{
					chongzhi(2);
			}
			if(m.x>=644&&m.x<=730&&m.y>=370&&m.y<=403)   //����
			{
				HWND wnd = GetHWnd();
				if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
					chongzhi(2);
			}

			if(m.x>=50 && m.x<=590&&m.y>=50 && m.y<=590 ) //���������ڣ�ʵ������
			{
			if((m.x-50)%30<=15)
				xx=(m.x-50)/30;
			else
				xx=(m.x-50)/30+1;
			if((m.y-50)%30<=15)
			yy=(m.y-50)/30;
			else
			yy=(m.y-50)/30+1;                          //������λ�������㴦�������ǵ������ġ�
			if(qipan[xx][yy]==0)
			{                                          //�˴��������ӣ����һ�����ӵ�ͼƬ������һ������
			putimage(xx*30+35,yy*30+35,&baizi);		  //��ȻҪ��XX,YYת��Ϊ��Ӧ�ڻ����ϵ�����
			mciSendString("seek mymusic to start", 0, 0, 0);
			mciSendString("play mymusic", NULL, 0, NULL);
			b++;
			}
			else continue;
			qipan[xx][yy]=1;
			judge(qipan,2);

			}


		}
		else                                  //���ӵĲ��֣������Ͱ���һ��
		{

			if(m.x>=644&&m.x<=730&&m.y>=304&&m.y<=340)
			{
				if(qipan[xx][yy]==0)
				{
					HWND wnd = GetHWnd();
					if (MessageBox(wnd, _T("������û������֪������Ĵ�����鷳��!!!"), _T("�Բ�!"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK);
				}
				else
				{
					putimage(xx*30+35,yy*30+35,&kongbai);
					qipan[xx][yy]=0;
					b--;
				}
			}
			if(m.x>=644&&m.x<=730&&m.y>=370&&m.y<=403)
			{
				HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
								chongzhi(2);
			}
			if(m.x>=680&&m.x<=733&&m.y>=8&&m.y<=61)
			{
				main();
			}
				if(m.x>=644&&m.x<=730&&m.y>=241&&m.y<=275)
			{
					chongzhi(2);}

				if(m.x>=50 && m.x<=590 && m.y>=50 && m.y<=590)
					{
						if((m.x-50)%30<=15)
							xx=(m.x-50)/30;
						else
							xx=(m.x-50)/30+1;
						if((m.y-50)%30<=15)
							yy=(m.y-50)/30;
						else
							yy=(m.y-50)/30+1;
						if(qipan[xx][yy]==0)
						{
							putimage(xx*30+35,yy*30+35,&heizi);
							mciSendString("seek mymusic to start", 0, 0, 0);
							mciSendString("play mymusic", NULL, 0, NULL);
							b++;
						}
						else continue;
						qipan[xx][yy]=2;
						judge(qipan,2);

					}

		}

		break;

		}

	}


	}

}
void singleplayer (void)				//�˻�����
{
	MOUSEMSG m;
	m=GetMouseMsg();

	int xx,yy;
		while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
	{
		case WM_LBUTTONDOWN:
		{

			if(m.x>=644&&m.x<=730&&m.y>=304&&m.y<=340)
			{
				if(qipan[jilu[0]][jilu[1]]==0&&qipan[jilu[2]][jilu[3]]==0)
				{
					HWND wnd = GetHWnd();
					if (MessageBox(wnd, _T("������û������֪������Ĵ�����鷳��!!!"), _T("�Բ�!"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK);
				}
				else    //ͨ������jilu����¼����������Ϣ���ڻ���ʱʵ��ȥ��һ��һ��
				{
					putimage(jilu[0]*30+35,jilu[1]*30+35,&kongbai);
					putimage(jilu[2]*30+35,jilu[3]*30+35,&kongbai);
					qipan[jilu[0]][jilu[1]]=0;
					qipan[jilu[2]][jilu[3]]=0;
				}
			}
			if(m.x>=644&&m.x<=730&&m.y>=241&&m.y<=275)
			{
				chongzhi(1);
			}
			if(m.x>=680&&m.x<=733&&m.y>=8&&m.y<=61)
			{
				main();
			}
			if(m.x>=644&&m.x<=730&&m.y>=370&&m.y<=403)
			{
				HWND wnd = GetHWnd();
							if (MessageBox(wnd, _T("����Ӯ"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
								chongzhi(1);
			}
			if(m.x>=50 && m.x<=590&&m.y>=50 && m.y<=590 )
			{
			if((m.x-50)%30<=15)
			xx=(m.x-50)/30;
			else
			xx=(m.x-50)/30+1;
			if((m.y-50)%30<=15)
			yy=(m.y-50)/30;
			else
			yy=(m.y-50)/30+1;
			if(qipan[xx][yy]==0)
			{
			putimage(xx*30+35,yy*30+35, &baizi);
			mciSendString("seek mymusic to start", 0, 0, 0);
			mciSendString("play mymusic", NULL, 0, NULL);
			}
			else continue;
			qipan[xx][yy]=1;
			if(judge(qipan,1)==0)
			{
			Sleep(500);
			ai();              //ÿ��һ�Ű��ӣ�ִ��һ��ai����������ӡ�
			judge(qipan,1);
			jilu[2]=xx;
			jilu[3]=yy;
			}
			}

		}
		break;

	}

	}
}

void ai (void)
{
	int k,i,j,s,t,max,p;
	int score_c[19][19]={0};             //��������������¼ÿ���հ׵�Ķ�Ӧ������
	int score_p[19][19]={0};             //�ֱ�Ϊ���Եķ���������ҵķ���

	for(i=1;i<19;i++)
	{
		for(j=1;j<19;j++)
		{
			if(qipan[i][j]==0)
			{
				qipan[i][j]=1;
				score_p[i][j]+=score(i,j,1); // ��¼���������ڴ˴����õ����ٷ�
				qipan[i][j]=2;
				score_c[i][j]+=score(i,j,-1); // ��¼����������ڴ˴����õ����ٷ�
				qipan[i][j]=0;
			}
		}
	}
// �ҵ�������Ŀ�λ���У�������Ժ������ڴ˴����õ����������ֵ
	for(s=t=i=1,max=score_c[1][1];i<19;i++)
	{
		for(j=1;j<19;j++)
		{
			if(score_c[i][j]>max)
			{
				max=score_c[i][j];        //ÿ�οյ㶼�ֱ���㡣 ���� ������ش˴���ֵ
				s=i;
				t=j;
			}
		}
	}
	for(i=1;i<19;i++)
	{
		for(j=1;j<19;j++)
		{
			if(score_p[i][j]>max)      //�����ֵ���ݸ�max�����ҽ��������괫�ݸ�s��t  ���ڶ�Ӧ��qipan��
			{
				max=score_p[i][j];
				s=i;
				t=j;
			}
		}
	}
	qipan[s][t]=2; // ����߷ִ�����
	putimage(s*30+35,t*30+35,&heizi);
	mciSendString("seek mymusic to start", 0, 0, 0);
	mciSendString("play mymusic", NULL, 0, NULL);
	jilu[0]=s;
	jilu[1]=t;
}

int score (int m,int n,int k)     //�Ʒֺ���
{
	int i,j,p=0,q=0,b[4]={0},x=0,shu,heng,zuoxie,youxie;
	int s;
	if (k==1)
		s=1;
	else
		s=2;
	for(i=m;i<m+5,i<19;i++)
	{
		if(qipan[i][n]!=s)
		{
			if(qipan[i][n]==0)
			{
				b[0]++;
			}
			break;
		}
		else
			p++;        //��һ������ִ�У�ÿ��������ͬ��ɫ�Ķ���1��
	}
	for(i=m-1;i>m-5,i>0;i--)
	{
		if(qipan[i][n]!=s)
		{
			if(qipan[i][n]==0)
			{
				b[0]++;
			}
			break;
		}
		else
			q++;   // ͬ�� �����������ң� ���ҵķ�������������Ϊ�˵��ں᷽���ϵķ���
	}
	heng=p+q;
	for(j=n,p=0;j<n+5.,j<19;j++)
	{
		if(qipan[m][j]!=s)
		{
			if(qipan[m][j]==0)
			{
				b[1]++;
			}
		break;
		}
		else
			p++;
	}
	for(j=n-1,q=0;j>n-5,j>0;j--)
	{
		if(qipan[m][j]!=s)
		{
			if(qipan[m][j]==0)
			{
				b[1]++;
			}
		break;
		}
		else
			q++;
	}
	shu=p+q;
	for(i=m,j=n,p=0;i<19,i<m+5,j<19;i++,j++)
	{
		if(qipan[i][j]!=s)
		{
			if(qipan[i][j]==0)
			{
				b[2]++;
			}
		break;
		}
		else
			p++;
	}
	for(i=m-1,j=n-1,q=0;i>0,i>m-5,j>0;i--,j--)
	{
		if(qipan[i][j]!=s)
		{
			if(qipan[i][j]==0)
			{
				b[2]++;
			}
			break;
		}
		else
			q++;
	}
	zuoxie=p+q;
	for(i=m,j=n,p=0;i>0,i>m-5,j<19;i--,j++)
	{
		if(qipan[i][j]!=s)
		{
			if(qipan[i][j]==0)
			{
				b[3]++;
			}
			break;
		}
		else
			p++;
	}
	for(i=m+1,j=n-1,q=0;i<19,i<m+5,j>0;i++,j--)
	{
		if(qipan[i][j]!=s)
		{
			if(qipan[i][j]==0)
			{
				b[3]++;
			}
			break;
		}
		else
			q++;
	}
	youxie=p+q;
	if(heng>4||shu>4||zuoxie>4||youxie>4)   //�����ĳ�������Ϸ��������ķ֣���˴������Ӯ����x��¼���� ������100��
	{
		x=100;
	}
	else
	{
		for(i=0;i<4;i++)
	{
	if(b[i]==0)           //b[]������˵������հ׵�ĸ����Ŀհ׵�ĸ���ͬ��û��ͬɫ���ӣ��ʷ�����20
	{
		b[i]=-20;
	}
}
	x=heng+b[0];
	if(shu+b[1]>x)
		x=shu+b[1];
	if(zuoxie+b[2]>x)
		x=zuoxie+b[2];
	if(youxie+b[3]>x)
		x=youxie+b[3];     //���ĸ�������ѡ��������ķ���ִ��
}
return x;           //���ش˵�ķ���
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/******************���һ��*******************/
/*****************����������******************/
/***************����� 2013242053*************/
/***************���ٻ� 2013242041*************/
/***************��ΰ�� 2013242045*************/
/***************������ 2013242080*************/
/****************��ӱ  2013242069*************/
/***************��ٻ�� 2013242049*************/
/***************��۳� 2013242005*************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
