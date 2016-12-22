#include "Collider.h"
#include "Output_Handler.h"
std::vector<std::shared_ptr<Collider>> Collider::_Colliders;
std::vector<std::shared_ptr<Collider>> Collider::_StaticColliders;



std::shared_ptr<Collider> Collider::Add(ent::Entity<> ent)
{
	if (!ent) { Output_Handler::Error << "ERR Collider::Add : No Entity supplied\n"; return nullptr; }
	auto c = std::make_shared<Collider>();
	ent->colliders.push_back(c);
	
	if (ent->movement)
		_Colliders.push_back(c);
	else
		_StaticColliders.push_back(c);
	c->_Parent = ent;

	return c;
}

bool Collider::Overlap(std::shared_ptr<Collider> c1, std::shared_ptr<Collider> c2)
{
	if (!c1 || !c2) { Output_Handler::Output << "MSG Collider::Overlap : No colliders supplied\n"; return false; }
	auto c1l = c1->_Parent->X - c1->W / 2;
	auto c1r = c1->_Parent->X + c1->W / 2;
	auto c1u = c1->_Parent->Y - c1->H / 2;
	auto c1d = c1->_Parent->Y + c1->H / 2;

	auto c2l = c2->_Parent->X - c2->W / 2;
	auto c2r = c2->_Parent->X + c2->W / 2;
	auto c2u = c2->_Parent->Y - c2->H / 2;
	auto c2d = c2->_Parent->Y + c2->H / 2;
	if (c1l > c2r || c1r < c2l || c1u > c2d || c1d < c2u) return false;
	return true;
}

void Collider::Update()
{
	//for (auto c = _Colliders.begin(); c != _Colliders.end(); ++c)
	//{
	//	for (auto c2 = c + 1; c2 != _Colliders.end(); ++c2)
	//	{
	//		//if (Overlap(c->get(), c2->get())) std::cout << "OVERLAP\n";
	//	}
	//	for (auto c2 = _StaticColliders.begin(); c2 != _StaticColliders.end(); ++c2)
	//	{
	//		if (Overlap(c->get(), c2->get())) std::cout << "OVERLAP STATIC\n";
	//	}
	//}
}

Collider::~Collider()
{
	for (auto c = _Colliders.begin(); c != _Colliders.end(); ++c)
		if (c->get() == this) { _Colliders.erase(c); break; }
	for (auto c = _StaticColliders.begin(); c != _StaticColliders.end(); ++c)
		if (c->get() == this) { _StaticColliders.erase(c); break; }
}
