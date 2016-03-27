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
	函数功能：实现二分查找

	参数说明：
		@arr[in]		待查找数组,递增
		@len[in]		数组长度
		@v[in]			待查找元素
		@index[out]		返回下标
		@min[in]		最小下标 or 最大下标

	函数说明：
		1.如果有多个匹配值，通过min参数指定返回下标最小的还是最大的。
		2.如果只有1个匹配值，那么返回唯一匹配值在数组中的下标。
		3.如果没有匹配值，通过min参数设置返回比查找值小一点或大一点值的下标。

		如有数组：1 2 2 4 4 4 7 7 9 10 11 11 14 19 21
		1.查找4 && min==true,那么返回index=3;(返回左边的4)
		2.查找4 && min==false,那么返回index=5;(返回右边的4)
		3.查找9不论min取何值都返回8;(唯一的9)
		4.查找5 && min==true,那么返回index=5;
		5.查找5 && min==false,那么返回index=6;
		6.如果被查找的元素不存在并且大于所有元素,并且min=false,那么返回最后超出位置
		7.如果被查找的元素不存在并且小于所有元素,并且min=true,那么返回开头超出位置(-1)

	函数返回：
		@return true	表示找到元素
		@return false	表示查找失败
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
			find = true;				//找到
			if ( min )
				end = mid - 1;
			else
				beg = mid + 1;
		}
		else if ( arr[mid] > v )
		{
			if ( !min && !find )
				index = mid;			//如果未找到记录大于v的下标
			end = mid - 1;
		}
		else
		{
			if( min && !find )
				index = mid;			//如果未找到记录小于v的下标
			beg = mid + 1;
		}
	}

	return find;
}


#endif