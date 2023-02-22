/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once


#include <sstream>
#include <stdexcept>
#include <cassert>

#include "slist.hpp"

template <class T>
SNode<T>::SNode (T const& it)
{
    //TODO
    this->_item = it;
    this->_next = nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //TODO
    this->_item = it;
    this->_next = next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //TODO
    //hint: if std::shared_ptr is used for the references, nothing todo.

    //
}

template <class T>
typename SNode<T>::Ref SNode<T>::create(T const& it, SNode<T>::Ref next)
{
    return std::make_shared<SNode<T>> (it, next);
}

template <class T>
T SNode<T>::item() const
{
    T it;
    //TODO
    it = this->_item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //TODO
    if(this->_next != nullptr){
        has = true;
    }
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //TODO
    n = this->_next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //TODO
    this->_item = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //TODO
    this->_next= n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //TODO
    this->head_ = nullptr;


    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //TODO



    //

}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //TODO
    h = this->head_;
    //
    return h;
}

template<class T>
typename SList<T>::Ref SList<T>::create()
{
    return std::make_shared<SList<T>> ();
}

template<class T>
typename SList<T>::Ref SList<T>::create(std::istream& in) noexcept(false)
{
    auto list = SList<T>::create();
    std::string token;
    in >> token;

    //TODO
    //Hint: use std::istringstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception when an input
    // format error was found.
    auto list_aux = SList<T>::create();//Creamos este auxiliar para poder ordenar los inputs

    if (token == "[]") //si esta vacio, devolvemos la lista
    {
        return list;
    }
    if (token != "[") //si no empieza por [, devolvemos el error
    {
        throw std::runtime_error("Wrong input format.");
    }

    T new_item;
    while (in >> token && token != "]")
    {
        std::istringstream string(token);
        string >> new_item;
        list_aux -> push_front(new_item);
    }

    while (!list_aux->is_empty())
    {
        list->push_front(list_aux->front());
        list_aux->pop_front();
    }

    if(token != "]")
    {
        throw std::runtime_error("Wrong input format.");
    }
    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //TODO
    if(this->head_ != nullptr){
        ret_val = false;
    }
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //TODO
    while(this->current_ != nullptr)
    {
    if(this->current_ != this->head_)
    {
        this->current_=this->head_;
        this->current_=this->current_->next();
        ret_val++;
    }
    else
    {
        this->current_->next();
        ret_val++;
    }
    }
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //TODO
    f = this->head_->item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(! is_empty());
    T c;
    //TODO
    c = this->current_->item();
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO
    if(this->current_->has_next() != false){
        ret_val = true;
    }
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //TODO
    if(this->has_next() == true){
        this->current_->next()->item();
        ret_val = true;
    }
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //TODO
    //Hint: you can reuse SList::find() but you must remember to restore 
    // the old the cursor position. In this way we assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    if (is_empty())
    {
        found = false;
    }

    typename SNode<T>::Ref nodo_aux = this->head_;
    if(nodo_aux -> item()== it)
    {
        found = true;
    }

    while (nodo_aux -> has_next())
    {
        nodo_aux = nodo_aux->next();
        if(nodo_aux->item()==it)
        {
            found = true;
        }
    }
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //TODO
    typename SNode<T>::Ref iterator = this->head_;

    out <<"["; // añadir al inicio la primera llave

    if (iterator != nullptr)
    {
        out << " ";
        out << this->head_->item();
        while(iterator->has_next())
        {
            iterator = iterator->next();
            out << " ";
            out << iterator ->item();
        }
        out <<" ";
    }
    out <<"]";

    //
}

template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //TODO
    this->current_->set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO
    //Remeber to update current if current is in the head.
    auto node = SNode<T>::create(new_it, this->head_);
    if(this->current_ == this->head_)
    {
        this->current_=node;
    }
    this->head_ == node;
    //
    assert(front()==new_it);
    assert(size() == (old_size+1));
}

template<class T>
void SList<T>::insert(T const& new_it)
{
#ifndef NDEBUG
    bool old_is_empty = is_empty();
    size_t old_size = size();
    T old_item;
    if (!old_is_empty)
        old_item = current();
#endif
    //TODO
    if (this->is_empty())
    {
        this->push_front(new_it);
        this->current_ = this->head_;
    }
    else
    {
        typename SNode<T>::Ref nodo = SNode<T>::create(new_it,this->current_->next());
        this->current_->set_next(nodo);
    }
    //
    assert(!old_is_empty || (front()==new_it && current()==new_it));
    assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
    assert(size()==(old_size+1));
}

template<class T>
void SList<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_head_next = head()->next();
#endif
    //TODO
    if (this->current_ == this->head_) //compruebo si estamos en head para asignar current al siguiente a la cabeza
    {
        this->current_ = this->head_->next();
    }
    this->head_ = this->head_->next();
    //
    assert(is_empty() || head() == old_head_next);
    assert(size() == (old_size-1));
}


template<class T>
void SList<T>::remove()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    bool old_has_next = has_next();
    T old_next;
    if (has_next())
        old_next=next();
#endif
    //TODO
    //Case 1: current is the head.
    if(this->current_ == this->head_)
    {
        pop_front();
        this->previous_ = nullptr;
        this->current_ = this->head_;
    }
    //Case 2: remove in a middle position.
    else
    {
        if (this->current_->has_next())
        {
            this->previous_->set_next(this->current_->next());
            this->current_ = this->current_->next();
        }

    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.
        else
        {
         find(this->previous_->item());
         this->current_->set_next(nullptr);
        }
    }
    //
    assert(!old_has_next || current()==old_next);
    assert(size() == (old_size-1));
}

template<class T>
void SList<T>::goto_next()
{
    assert(has_next());
#ifndef NDEBUG
    auto old_next = next();
#endif
    //TODO
    this->previous_ = this->current_;
    this->current_ = this->current_->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //TODO
    this->current_ = this->head_;
    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //TODO
    this->current_ = this->head_;

    while(this->current_->has_next() && !found)
    {
        if(this->current_->item() == it)
        {
            found = true;
            break;
        }

        this->previous_ = this->current_;
        this->current_ = this->current_->next();
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

template<class T>
bool SList<T>::find_next(T const& it)
{
    assert(has_next());
    bool found = false;
    //TODO
    while(this->current_->has_next() && !found)
    {
        this->previous_ = this->current_;
        this->current_ = this->current_->next();
        if(this->current_->item() == it)
        {
            found = true;
        }
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

