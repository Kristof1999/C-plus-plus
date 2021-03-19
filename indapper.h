#ifndef INDAPPER_H
#define INDAPPER_H
#include <vector>
#include <numeric>

template <class ContainerType, typename ContainerItemType = typename ContainerType::value_type>
class index_appender_view
{
	struct AccumulateHelper
	{
		int operator()(int x, ContainerType* y)
		{
			return x + y->size();
		}
	}AccHelper;
	public:
	index_appender_view() : view()
	{}
	index_appender_view(const index_appender_view &obj) : view(obj.view)
	{}
	
	const ContainerItemType& at(unsigned int pos) const
	{
		unsigned int i = 0;
		while(i < view.size() && pos >= view[i]->size())
		{
			pos -= view[i]->size();
			i++;
		}
		return view[i]->at(pos);
	}
	ContainerItemType& at(unsigned int pos)
	{
		unsigned int i = 0;
		while(i < view.size() && pos >= view[i]->size())
		{
			pos -= view[i]->size();
			i++;
		}
		return view[i]->at(pos);
	}
	const ContainerItemType& operator[](int pos) const
	{
		return at(pos);
	}
	ContainerItemType& operator[](int pos)
	{
		return at(pos);
	}
	int size() const
	{
		return std::accumulate(view.begin(), view.end(), 0, AccHelper);
	}
	void add(ContainerType &container)
	{
		view.push_back(&container);
	}
	
	private:
	std::vector<ContainerType*> view;
	//Ha egy ContainerType tipusu kontener kivulrol valtozik, akkor nem biztos, hogy az objektum
	//belso reprezentaciojaban is valtozni fog az adataszerkezet.
	//Ahhoz, hogy ez megis megtortenjen, ContainerType-ra mutato pointereket tarolunk.
	//Referenciakkal nem mukodne a vector sajatossagai miatt.
};

template<>
class index_appender_view<std::vector<bool>>
{
	struct AccumulateHelper
	{
		int operator()(int x, std::vector<bool>* y)
		{
			return x + y->size();
		}
	}AccHelper;
	public:
	index_appender_view() : view()
	{}
	index_appender_view(const index_appender_view &obj) : view(obj.view)
	{}
	
	bool at(unsigned int pos) const
	{
		unsigned int i = 0;
		while(i < view.size() && pos >= view[i]->size())
		{
			pos -= view[i]->size();
			i++;
		}
		return view[i]->at(pos);
	}
	std::vector<bool>::reference at(unsigned int pos)
	{
		unsigned int i = 0;
		while(i < view.size() && pos >= view[i]->size())
		{
			pos -= view[i]->size();
			i++;
		}
		return view[i]->at(pos);
	}
	bool operator[](int pos) const
	{
		return at(pos);
	}
	std::vector<bool>::reference operator[](int pos)
	{
		return at(pos);
	}
	int size() const
	{
		return std::accumulate(view.begin(), view.end(), 0, AccHelper);
	}
	void add(std::vector<bool> &container)
	{
		view.push_back(&container);
	}
	
	private:
	std::vector<std::vector<bool>*> view;
	//A feladat sajatossaga miatt (ld. 79. es 83. sorok) nem lenne eleg bool* view
};

#endif //INDAPPER_H