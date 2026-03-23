#pragma once

// public virtual destructor to make it polymorphic(required for dynamic_cast)
class Base
{
	public:
		virtual ~Base() {}
};

// Classes A, B and C publicly inherit from Base.
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);
