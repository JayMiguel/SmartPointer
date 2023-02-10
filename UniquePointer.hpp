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
	// ����
	UniquePointer(T* ptr = nullptr, void (*deleter)(T*) = nullptr) : p(ptr)
	{
		this->deleter = deleter ? deleter : DefaultDeleter<T>;
	}

	// �ƶ�����
	UniquePointer(UniquePointer<T>& other)
	{
		p = other.Release();
		deleter = other.deleter;
	}

	// ����
	~UniquePointer()
	{
		if (p)
		{
			deleter(p);
		}
	}

	// ��ֵ�����
	void operator=(UniquePointer<T>& other)
	{
		if (p != other.p)
		{
			deleter(p);
			p = other.Release();
			deleter = other.deleter;
		}
	}

	// ָ�������
	T* operator->()
	{
		return p;
	}

	T const* operator->() const
	{
		return p;
	}

	// ������
	T operator*()
	{
		return *p;
	}

	// �±������
	T operator[](int index)
	{
		return p[index];
	}

	// ������Դ
	T* Release()
	{
		T* ptr = p;
		p = nullptr;
		return ptr;
	}

private:

	// ԭʼָ��
	T* p;

	// ɾ����
	void (*deleter)(T*);
};