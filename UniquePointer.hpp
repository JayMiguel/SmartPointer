#pragma once

template <typename T>
void DefaultDeleter(T* p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
class UniquePointer
{
public:
	// 构造
	UniquePointer(T* ptr = nullptr, void (*deleter)(T*) = nullptr) : p(ptr)
	{
		this->deleter = deleter ? deleter : DefaultDeleter<T>;
	}

	// 移动构造
	UniquePointer(UniquePointer<T>& other)
	{
		p = other.Release();
		deleter = other.deleter;
	}

	// 析构
	~UniquePointer()
	{
		if (p)
		{
			deleter(p);
		}
	}

	// 赋值运算符
	void operator=(UniquePointer<T>& other)
	{
		if (p != other.p)
		{
			deleter(p);
			p = other.Release();
			deleter = other.deleter;
		}
	}

	// 指针运算符
	T* operator->()
	{
		return p;
	}

	T const* operator->() const
	{
		return p;
	}

	// 解引用
	T operator*()
	{
		return *p;
	}

	// 下标操作符
	T operator[](int index)
	{
		return p[index];
	}

	// 放弃资源
	T* Release()
	{
		T* ptr = p;
		p = nullptr;
		return ptr;
	}

private:

	// 原始指针
	T* p;

	// 删除器
	void (*deleter)(T*);
};