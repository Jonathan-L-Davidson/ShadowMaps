#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

class Object;

class Component
{
	public:
		Component();
		~Component();

		virtual void Awake(Object* owner);
		virtual void Start();
		virtual void Update();
		virtual void Destroy();

		virtual void Attach(Object* obj);
		virtual void Detach(Object* obj);
	private:
		Object* _owner; // Object it's attached to.
};

#endif