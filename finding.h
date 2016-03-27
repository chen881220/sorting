#ifndef _FINDING_H_
#define _FINDING_H_

#include <cassert>

namespace finding
{
	template<typename ELEM>
	bool BinFindIndex(ELEM *arr,int len,const ELEM &v,int &index,bool min = true);
}

/************************************************************************/
/* 
	�������ܣ�ʵ�ֶ��ֲ���

	����˵����
		@arr[in]		����������,����
		@len[in]		���鳤��
		@v[in]			������Ԫ��
		@index[out]		�����±�
		@min[in]		��С�±� or ����±�

	����˵����
		1.����ж��ƥ��ֵ��ͨ��min����ָ�������±���С�Ļ������ġ�
		2.���ֻ��1��ƥ��ֵ����ô����Ψһƥ��ֵ�������е��±ꡣ
		3.���û��ƥ��ֵ��ͨ��min�������÷��رȲ���ֵСһ����һ��ֵ���±ꡣ

		�������飺1 2 2 4 4 4 7 7 9 10 11 11 14 19 21
		1.����4 && min==true,��ô����index=3;(������ߵ�4)
		2.����4 && min==false,��ô����index=5;(�����ұߵ�4)
		3.����9����minȡ��ֵ������8;(Ψһ��9)
		4.����5 && min==true,��ô����index=5;
		5.����5 && min==false,��ô����index=6;
		6.��������ҵ�Ԫ�ز����ڲ��Ҵ�������Ԫ��,����min=false,��ô������󳬳�λ��
		7.��������ҵ�Ԫ�ز����ڲ���С������Ԫ��,����min=true,��ô���ؿ�ͷ����λ��(-1)

	�������أ�
		@return true	��ʾ�ҵ�Ԫ��
		@return false	��ʾ����ʧ��
*/
/************************************************************************/
template<typename ELEM>
bool finding::BinFindIndex(ELEM *arr,int len,const ELEM &v,int &index,bool min)
{
	assert(len>=0);
	assert(arr!=NULL);

	index = -1;

	int beg = 0;
	int end = len;
	bool find = false;

	while ( beg <= end )
	{
		int mid = (beg+end)/2;
		if ( arr[mid] == v )
		{
			index = mid;
			find = true;				//�ҵ�
			if ( min )
				end = mid - 1;
			else
				beg = mid + 1;
		}
		else if ( arr[mid] > v )
		{
			if ( !min && !find )
				index = mid;			//���δ�ҵ���¼����v���±�
			end = mid - 1;
		}
		else
		{
			if( min && !find )
				index = mid;			//���δ�ҵ���¼С��v���±�
			beg = mid + 1;
		}
	}

	return find;
}


#endif