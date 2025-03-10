#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

class Object;

class Component
{
	public:
		Component();
		~Component();

		virtual void Awake();
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void Destroy();

		virtual void Attach(Object* obj);
		virtual void Detach(Object* obj);
	protected:
		Object* _owner; // Object it's attached to.
};

#endif