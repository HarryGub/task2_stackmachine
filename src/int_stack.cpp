////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"

#include <stdexcept>

namespace xi {
    // Constructors
    IntStack::IntStack(size_t sz){
        _ssize = sz;
        _stack = new int[STACK_SIZE];
        _head = 0;
    }
    IntStack::~IntStack(){
        delete[] _stack;
        _ssize = 0;
        _head = 0;
    }

    void IntStack::push(int el){
        if(isFull()){
            throw std::logic_error("Stack is already full!");
        } else{
            _stack[_head] = el;
            _head++;
        }
    }

    int IntStack::pop(){
        if(isEmpty()){
            throw std::logic_error("Stack is empty!");
        } else{
            int res = _stack[_head - 1];
            _head--;
            _stack[_head] = 0;
            return res;
        }
    }

    int IntStack::top(){
        if(isEmpty()){
            throw std::logic_error("Stack is empty!");
        } else{
            return _stack[_head - 1];
        }
    }

    void IntStack::clear(){
        for(int i = 0; i < _head;i++){
            _stack[i] = 0;
        }
        _head = 0;
    }

    bool IntStack::isEmpty() const{
        if(_head == 0){
            return true;
        } else{
            return false;
        }
    }

    bool IntStack::isFull() const{
        if(_head == _ssize){
            return true;
        } else{
            return false;
        }
    }

}

