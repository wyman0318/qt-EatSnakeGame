
#include "tty.h"


static struct timeval timeout;


/* ���ô��ڲ���:115200���� */
void init_tty(int fd)
{    
	//�������ô��ڵĽṹ��
	struct termios termios_new;
	//����ոýṹ��
	bzero( &termios_new, sizeof(termios_new));
	//	cfmakeraw()�����ն����ԣ���������termios�ṹ�еĸ���������
	cfmakeraw(&termios_new);
	//���ò�����
    cfsetispeed(&termios_new, B115200);
    cfsetospeed(&termios_new, B115200);
	//CLOCAL��CREAD�ֱ����ڱ������Ӻͽ���ʹ�ܣ���ˣ�����Ҫͨ��λ����ķ�ʽ����������ѡ�    
	termios_new.c_cflag |= CLOCAL | CREAD;
	//ͨ��������������λΪ8λ
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 
	//��������żУ��
	termios_new.c_cflag &= ~PARENB;
	//һλֹͣλ
	termios_new.c_cflag &= ~CSTOPB;
	tcflush(fd,TCIFLUSH);
	// �����ý����ַ��͵ȴ�ʱ�䣬������Ҫ����Խ�������Ϊ0
	termios_new.c_cc[VTIME] = 10;
	termios_new.c_cc[VMIN] = 1;
	// �����������/���������
	tcflush (fd, TCIFLUSH);
	//������ú󣬿���ʹ�����º������������
	if(tcsetattr(fd,TCSANOW,&termios_new) )
		printf("Setting the serial1 failed!\n");

}

int tty_starts()
{
//	int ret, i;
    int fd2;

//	fd1 = open(DEV_PATH1, O_RDWR | O_NOCTTY);
//	if (fd1 < 0)
//	{
//		fprintf(stderr, "Open ttySAC1 fail!\n");
//		return -1;
//	}
	
	fd2 = open(DEV_PATH2, O_RDWR | O_NOCTTY );
	if (fd2 < 0)
	{
		fprintf(stderr, "Open ttySAC2 fail!\n");
		return -1;
	}
	//��ʼ������
//	init_tty(fd1);
	init_tty(fd2);
	
//	char buf[20];
//	while(1){
		
//		bzero(buf,20);
//		fgets(buf,20,stdin);
//		write(fd1,buf,strlen(buf));
		
//		bzero(buf,20);
//		read(fd2,buf,20);
//		printf("tty2:%s\n",buf);
		
//		if(strcmp(buf,"over\n")==0)break;
		
//	}
	
	
//	close(fd1);
//	close(fd2);
    return fd2;
}

//�����ļ� ���ļ����������file_name���ļ���  size���ļ���С data������������
//u8* find_data(char *file_name, unsigned int *size, u8 *data)
//{
//    u8 *p = data;
//    int len = 0;
//    if((file_name == NULL) || (size == NULL))//Ϊ�վ��˳�
//        return NULL;
//    while(*p++)//�����ж��ٸ�#���С��2Ҳ���ǲ���3��#���˳�
//    {
//        if(*p == '#')
//            len++;
//    }
//    if(len != 2)
//        return NULL;
//    len = 0;
//    p = strtok(data, "#");
//    while(p != NULL)
//    {
//        //printf("--find_data-- %s\n", p);
//        if(len == 0 )
//            strcpy(file_name, p);
//        else if(len == 1)
//        {
//            *size = atoi(p);
//            p = strtok(NULL, "#");
//            break;
//        }
//        p = strtok(NULL, "#");
//        len++;
//    }

//    return p;
//}

//void file_rev(int fd)
//{
//    int len;
//    char buff[256]={0};
//    char file_name[100] = {0};//�ļ���
//    char temp[256] = {0};
//    int file_fd = 0;//���յ������ļ�������
//    int file_all_len = 0;//�ļ����ܴ�С�жԷ��������õ�
//    int file_recv_len = 0;//ÿ�λ�ȡ���ļ����ݴ�С
//    bool flag = true;//�ļ���־λ��true�ǵ�һ��Ҫ������

//    while(1)
//    {
//            //�ļ����ղ���
//            len = read(fd, buff, sizeof(buff));
//            printf("read_file-- %s\n", buff);
//            if(flag == true)//��һ�ν���Ҫ����ļ�����ȡ#�ļ�����#�ļ�����#
//            {
//                    //�ַ���ƴ��
//                    strcat(temp, buff);
//                    printf("--bufffile-- %s\n", temp);
//                    u8 *p = find_data(file_name, &file_all_len, temp);//�������ݽ��ļ�������,�ļ��Ĵ�С���Һ���
//                    //���ʧ�� ΪNULL ���½���continue ����ƴ���µ����ݣ�����ַ��� ֱ��temp>172�ַ��ͻ�����û��ϣ����
//                    if(p == NULL)
//                    {
//                            //printf("recv data continue \n");
//                            if(172 < strlen(temp))//һֱû���ҵ��ļ����ֺʹ�С������Ҳװһ�룬�Ǿ��Ǵ�����
//                                    break;
//                            continue;
//                    }
//                    printf("filename %s , filesize %d\n", file_name, file_all_len);
//                    file_fd = open(file_name, O_RDWR | O_CREAT, 0777); //������д���ļ�
//                    if(file_fd < 0)//��ʧ�ܾ��˳�ѭ��
//                    {
//                            perror("file_fd file error");
//                            break;
//                    }
//                    file_recv_len += write(file_fd, p, strlen(p));
//                    if(file_recv_len == file_all_len)//�����Ⱦ�ֱ���˳�
//                    {
//                            printf("false recv done name %s,size %d\n", file_name, file_all_len);
//                            close(file_fd);
//                            break;
//                    }
//                    flag = false;
//                    printf("file_recv_len true %d p-> %s buff -->%s\n", file_recv_len, p, buff);
//            }
//            else//�ļ��Ѿ��������ˣ�ֱ�Ӱ�װ
//            {
//                    file_recv_len += len;//�������پ�д�����
//                    write(file_fd, buff, len);
//            }
//            if(file_recv_len == file_all_len)//�ļ��ܴ�С���ļ������ݶ�ȡ�Ĵ�С���
//            {
//                    printf("true recv done name %s,size %d\n", file_name, file_all_len);
//                    close(file_fd);
//                    flag = true;
//                    break;
//            }
//    }
//}
