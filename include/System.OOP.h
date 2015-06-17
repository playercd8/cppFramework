/*
* System.OOP.h
*
* Code Status: Drafts
*  Created on: Taiwan
*      Author: player
*/

#ifndef SYSTEM_OOP_H_
#define SYSTEM_OOP_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "System.Collections.List.h"
#include "System.Collections.Map.h"
#include "System.Collections.Queue.h"
#include "System.String.h"
using namespace System::Collections;

namespace System {

	//---------------------------------------------------------------------------------------------------------
	// template class IAttributes
#pragma region template class IAttributes
	template <typename Key, typename Values>
	class IAttributes {
		Map<Key, Values>	_all;
	public:
		IAttributes() {}
		virtual ~IAttributes() {
			_all.RemoveAll();
		}

		void Add(Key& keyID, Values& Value) {
			_all.SetAt(keyID, Value);
		}

		Values Get(Key& keyID, Values& DefaultValue) {
			Values val;
			if (_all.Lookup(keyID, val))
				return val;
			return DefaultValue;
		}

		void Remove(Key& keyID) {
			_all.RemoveKey(keyID);
		}

		bool IsEmpty() const {
			return _all.empty();
		}
	};
#pragma endregion template class IAttributes

	//---------------------------------------------------------------------------------------------------------
	// template class IClone
#pragma region template class IClone
	template <typename T>
	class IClone {
	public:
		virtual T* Clone() = 0;
	};
#pragma region template class IClone

	//---------------------------------------------------------------------------------------------------------
	// template class Observer
#pragma region template class Observer
	template <typename Event>
	class IObserver {
	public:
		virtual void Notify(Event& e) = 0;
	};

	template <typename Event>
	class Observer {
		typedef typename IObserver<Event> Interface;
	private:
		List<Interface*> _observers;
	public:
		Observer() {}
		virtual ~Observer() {
			deleteObservers();
		}

		void HookObserver(Interface* pObj) {
			_observers.AddTail(pObj);
		}

		int GetCount() {
			return _observers.GetCount();
		}

		void UnHookObserver(Interface* pObj) {
			List<Interface*>::Iterator iter = _observers.GetHeadPosition();
			while (_observers.iteratorValid(iter)) {
				if ((*iter) == pObj) {
					_observers.RemoveAt(iter);
					return;
				}				
			}
		}
		
		void deleteObservers() {
			_observers.RemoveAll();
		}

		void Notify(Event& e) {
			List<Interface*>::Iterator iter = _observers.GetHeadPosition();
			while (_observers.iteratorValid(iter)) {
				(*iter)->Notify(e);
			}
		}
	};
#pragma endregion template class Observer


	//---------------------------------------------------------------------------------------------------------
	// template class IFactory
#pragma region template class IFactory
	template <typename T>
	class IFactory {
	public:
		IFactory() {}
		virtual ~IFactory() {}

		virtual T GetObject(LPCTSTR pObjName);
		virtual void ReleaseObject(LPCTSTR pObjName);
		virtual void ReleaseAllObject();
	};
#pragma endregion template class IFactory

	//---------------------------------------------------------------------------------------------------------
	// class template ShareObject
#pragma region template class ShareObject
	template <typename T>
	class ShareObject {
	private:
		volatile unsigned long _refCount;
		IFactory<T> _pFactory;
		String _strName;

	public:
		ShareObject(IFactory<T>* pFactory, String strName) :
			_pFactory(pFactory),
			_strName(strName),
			_refCount(0) {
		}

		virtual ~ShareObject() {
		}

		void AddRef() {
			_refCount++;
		}

		void Release()
		{
			_refCount--;
			if (_refCount <= 0)	{
				if (_pFactory) {
					_pFactory->ReleaseObject(_strName);
					//delete this;
				}
			}
		}
	};
#pragma endregion template class ShareObject

	//---------------------------------------------------------------------------------------------------------
	// class template Singleton
#pragma region template class Singleton
	template <typename T>
	class Singleton {
	public:
		Singleton() {}
		virtual ~Singleton() {}

		static T* GetInstance() {
			static T _Instance;
			return &_Instance;
		}
	};
#pragma endregion template class Singleton


	//---------------------------------------------------------------------------------------------------------
	// class template ObjectPool
#pragma region template class ObjectPool
	template <typename T>
	class ObjectPool {
	private:
		Queue<T*> _pool;

	public:
		ObjectPool(int initCount) {
			for (int i = 0; i < initCount; i++)
				_pool.AddTail(CreateObject());
		}

		virtual ~ObjectPool() {
			T* obj;
			while (obj = _pool.GetFromFront()) {
				delete obj;
			}
		}

		virtual T* CreateObject() = 0;

		T* GetObject() {
			T* obj = _pool.GetFromFront();
			if (obj == NULL) {
				obj = CreateObject();
			}
			return obj;						
		}

		void ReleaseObject(T* obj) {
			if (obj) {
				_pool.AddTail(obj);
			}
		}
	};
#pragma endregion template class ObjectPool
} /* namespace System */

#endif /* SYSTEM_OOP_H_ */
