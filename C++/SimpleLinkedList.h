#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H

#include <memory>


template <typename T>
class SimpleLinkedList
{
private:
  struct LLNode;
  using LLLink = std::unique_ptr<LLNode>;
  struct LLNode
  {
    LLNode(T&& v_, LLLink&& next_) : v(std::move(v_)), next(std::move(next_)){}
    LLNode(const T& v_, LLLink&& next_) : v(v_), next(std::move(next_)){}

    T v;
    LLLink next;
  };
  using LL = LLLink;


  LL vs;

public:
  using element_type = T;

  class SimpleIterator
  {
  private:
    const LLNode* i;
  public:
    using element_type = T;

    SimpleIterator(const LLLink& link): i(link.get()){}
    SimpleIterator& operator++(){i = i->next.get();return *this;}
    SimpleIterator operator++(int){const auto old = *this;++(*this);return old;}
    const T& operator*() const noexcept {return i->v;}
    const T* operator->() const noexcept {return &(i->v);}
    bool at_end() const noexcept {return i == nullptr;}
    SimpleIterator next() const noexcept {auto next_iter = *this; ++next_iter;return next_iter;}
 };

  SimpleLinkedList(){}
  SimpleLinkedList(SimpleLinkedList&& other) :vs(std::move(other.vs)){}
  ~SimpleLinkedList()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  void push_front(const T& v)
  {
    auto front_link = std::make_unique<LLNode>(v,std::move(vs));
    vs.swap(front_link);
  }
  void push_front(T&& v)
  {
    auto front_link = std::make_unique<LLNode>(std::move(v),std::move(vs));
    vs.swap(front_link);
  }

  void pop_front()
  {
    LLLink front_link{};
    vs.swap(front_link);
    vs.swap(front_link->next);
  }

  const T& front() const noexcept
  {
    return *vs;
  }

  bool empty() const noexcept {return vs == nullptr;}

  SimpleIterator begin() const noexcept {return SimpleIterator(vs);}
};



#endif //SIMPLELINKEDLIST_H
