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
    _item = new_it;
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
    this->current_= nullptr;
    this->previous_= nullptr;
    this->Tam = 0;
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
    h = head_;
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
    if (token == "[]") // si esta vacia devuelve la lista.
    {
        return list;
    }
    if (token != "[") // si no empieza con "[" devuelve error.
    {
        throw std::runtime_error("Wrong input format.");
    }

    T new_item;
    auto list_aux = SList<T>::create(); // crear una lista auxiliar para los inputs.
    while (in >> token && token != "]")
    {
        std::istringstream string(token);
        if (!(string >> new_item)) // comprueba si el token puede ser convertido a tipo T.
        {
            throw std::runtime_error("Wrong input format.");
        }
        list_aux->push_front(new_item);
    }

    if (token != "]")
    {
        throw std::runtime_error("Wrong input format.");
    }

    while (!list_aux->is_empty())
    {
        list->push_front(list_aux->front());
        list_aux->pop_front();
    }
    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //TODO
    if(head_ != nullptr){
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
    ret_val = this->Tam;
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //TODO
    f = head_->item();
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
    if(current_->has_next() != false){
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
        ret_val= current_->next()->item();


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
    typename SNode<T>::Ref iterator = head_;

    if(is_empty()){
        out<<"[]";
    }else{
        out<<"[";

        while(iterator !=nullptr){
            out<<" "<<iterator->item();
            iterator = iterator->next();
        }
        out <<" ";
    }
    out<<"]";
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
    if(is_empty())
    {
        head_ = SNode<T>::create(new_it,head_);
        current_ = head_;
        this->Tam = Tam+1;
    }else{
        auto newHead = SNode<T>::create(new_it,head_);
        head_ = newHead;
        current_ = head_;
        this->Tam = Tam+1;
    }
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
    if(is_empty())
    {
        push_front(new_it);
    }else{
        auto newNode = SNode<T>::create(new_it,current_->next());
        current_->set_next(newNode);
        this->Tam = Tam+1;
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
    if (head_->has_next()) //compruebo si estamos en head para asignar current al siguiente a la cabeza
    {
        head_ = head_->next();
        current_= head_;
        this->Tam = Tam-1;
    }
    else
    {
        head_ = nullptr;
        current_ = head_;
        this->Tam = Tam-1;
    }
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
    if(current_ == head_)
    {
        pop_front();
        this->previous_ = nullptr;
        this->current_ = this->head_;
    }
    //Case 2: remove in a middle position.
    else
    {
        if (current_->has_next())
        {
            auto auxNode = head_;
            while(auxNode->next() != current_)
            {
                auxNode = auxNode->next();
            }

            auxNode->set_next(current_->next());
            current_=current_->next();
            this->Tam = Tam-1;
        }

    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.
        else
        {
            auto auxNode = head_;
            while(auxNode->next() != current_)
            {
                auxNode = auxNode->next();

            }

            auxNode->set_next(nullptr);
            current_ = auxNode;
            this->Tam = Tam-1;
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
    current_ = current_->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //TODO
    current_ = head_;
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

    for(int i = 0; i<this->size(); i++)
    {
        if (this->current_->item() == it)
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
    current_ = current_->next();

    while( current_ != nullptr ){
        if(current_->item() == it){
            found = true;
            return found;
        }

        current_ = current_->next();
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

