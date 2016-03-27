#ifndef _SORTING_H_
#define _SORTING_H_

#include "finding.h"
using namespace std;

namespace sorting
{
	template<typename ELEM>
	void Swap(ELEM &a,ELEM &b);

	template<typename ELEM>
	void Reverse(ELEM *array,size_t len);

	//希尔排序属于分组的直接插入排序,此处stop是留给希尔排序的.
	template<typename ELEM>
	void InsertSort(ELEM *array,size_t len,int step = 2);

	template<typename ELEM>
	void HalfSort(ELEM *array,size_t len);

	template<typename ELEM>
	void Bubble(ELEM *array,size_t len);

	template<typename ELEM>
	void Select(ELEM *array,size_t len);

	template<typename ELEM>
	void Shell(ELEM *array,size_t len,size_t *dt,size_t dt_len);

	template<typename ELEM>
	void Quick(ELEM *array,int beg,int end);

	template<typename ELEM>
	void Merge(ELEM *array,int beg,int end);

	template<typename ELEM>
	void sift_heap(ELEM *array,size_t end,int index);

	template<typename ELEM>
	void Heap(ELEM *array,size_t end);

	template<typename ELEM>
	bool test(ELEM *array,size_t len);
}

#include "sorting.h"

template<typename ELEM>
void sorting::Swap(ELEM &a,ELEM &b)
{
	ELEM tmp = a;
	a = b;
	b = tmp;
}

template<typename ELEM>
void sorting::Reverse(ELEM *array,size_t len)
{
	for ( size_t ii=0; ii<len/2; ++ii )
		sorting::Swap(array[ii],array[len-ii-1]);
}

/************************************************************************/
/* 
	函数功能：插入排序
	函数参数：
		@array	:待排序数组
		@len	:数组长度,可用范围array[0]—array[len-1]
		@step	:步长,默认为2
	函数说明：
		当步长为2时算法属于插入排序,当步长大于2时可实现希尔排序.
		由于希尔排序就是分组的插入排序,此处step参数留个希尔排序.
*/
/************************************************************************/
template<typename ELEM>
void sorting::InsertSort(ELEM *array,size_t len,int step)
{
	size_t dt = step - 1;
	for ( size_t ii=dt; ii<len; ++ii )
	{
		ELEM tmp = array[ii];
		size_t index = ii;

		while ( index>0 && array[index-dt]>tmp )
		{
			array[index] = array[index-dt];
			index -= dt;
		}

		array[index] = tmp;
	}
}

/************************************************************************/
/* 
	函数功能：折半插入排序
	函数参数：
		@array	:待排序数组
		@len	:array[0]—array[len-1]
	函数说明：
		通过BinFindIndex实现二分查找.
*/
/************************************************************************/
template<typename ELEM>
void sorting::HalfSort(ELEM *array,size_t len)
{
	for ( size_t ii=1; ii<len; ++ii )
	{
		ELEM tmp = array[ii];
		int index = 0;
		finding::BinFindIndex(array,ii,tmp,index,false);

		assert(index!=-1);

		for ( int jj=ii; jj>index; --jj )
			array[jj] = array[jj-1];

		array[index] = tmp;
	}
}

template<typename ELEM>
void sorting::Bubble(ELEM *array,size_t len)
{
	for ( size_t ii=0; ii<len-1; ++ii )
	{
		bool b = false;
		for ( size_t jj=0; jj<len-1-ii; ++jj )
			array[jj]>array[jj+1]?Swap(array[jj],array[jj+1]),b=true:NULL;

		//如果某行没有冒泡表示已有序
		if ( !b )
			break;
	}
}

template<typename ELEM>
void sorting::Select(ELEM *array,size_t len)
{
	for ( size_t ii=0; ii<len; ii++ )
	{
		size_t index = ii;
		for ( size_t jj=ii+1; jj<len; ++jj )
			array[jj]<array[index]?index=jj:NULL;
		
		sorting::Swap(array[ii],array[index]);
	}
}

template<typename ELEM>
void sorting::Shell(ELEM *array,size_t len,size_t *dt,size_t dt_len)
{
	//以分组形式调用直接插入排序.
	for ( size_t ii=0; ii<dt_len; ++ii )
		InsertSort(array,len,dt[ii]);
}

/************************************************************************/
/* 
	函数功能：快速排序
	函数参数：
		@array	:待排序数组
		@beg	:待排序起点
		@end	:待排序终点
		范围array[beg]—array[end],可以取到array[end].
*/
/************************************************************************/
template<typename ELEM>
void sorting::Quick(ELEM *array,int beg,int end)
{
	if ( beg >= end)
		return ;

	ELEM tmp = array[beg];
	int iBeg = beg;
	int iEnd = end;

	while ( iBeg < iEnd )
	{
		while ( iBeg<iEnd && array[iEnd]>=tmp )
			--iEnd;

		if ( iBeg == iEnd )
			break;

		array[iBeg++] = array[iEnd];

		while ( iBeg<iEnd && array[iBeg]<=tmp )
			++iBeg;

		array[iEnd--] = array[iBeg];
	}

	//最后是++iBeg,所以最终位置是iBeg.
	array[iBeg] = tmp;

	Quick(array,beg,iBeg-1);
	Quick(array,iBeg+1,end);
}

/************************************************************************/
/* 
	函数功能：归并排序
	参数说明：
		如果参数为end那么可以取到array[end]
		如果参数为len那么只能取到array[len-1]
*/
/************************************************************************/
template<typename ELEM>
void sorting::Merge(ELEM *array,int beg,int end)
{
	if ( beg < end )
	{
		int mid = (beg+end)/2;
		Merge(array,beg,mid);
		Merge(array,mid+1,end);

		int indexA = beg;
		int indexB = mid+1;
		ELEM *buf = new ELEM[end+1];
		size_t index  = 0;

		while ( indexA<=mid && indexB<=end )
		{
			if ( array[indexA] < array[indexB] )
				buf[index++] = array[indexA++];
			else
				buf[index++] = array[indexB++];
		}

		while ( indexA <= mid )
			buf[index++] = array[indexA++];

		while ( indexB <= end )
			buf[index++] = array[indexB++];

		//一定要从ii+beg开始复制.
		for ( size_t ii=0; ii<index; ++ii )
			array[ii+beg] = buf[ii];

		delete buf;
	}
}

template<typename ELEM>
void sorting::sift_heap(ELEM *array,size_t end,int index)
{
	ELEM tmp = array[index];
	size_t child = index<<1;

	while ( child <= end )
	{
		if ( child<=end-1 && array[child]<array[child+1] )
			child = child + 1;

		if ( array[child] <= tmp )
			break;
		else
		{
			array[index] = array[child];
			index = child;
			child = child<<1;
		}
	}

	array[index] = tmp;
}

template<typename ELEM>
void sorting::Heap(ELEM *array,size_t end)
{
	for ( size_t ii=end/2; ii>=1; ii-- )
		sift_heap(array,end,ii);

	for ( size_t ii=end; ii>=2; --ii )
	{
		sorting::Swap(array[1],array[ii]);
		sift_heap(array,ii-1,1);
	}
}

template<typename ELEM>
bool sorting::test(ELEM *array,size_t len)
{
	for ( size_t ii=0; ii<len-1; ++ii )
		if ( array[ii] > array[ii+1] )
			return false;

	return true;
}

#endif