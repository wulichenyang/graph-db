#pragma once
enum class RelationshipDirection
{
	OUTGOING,
	INCOMING,
	LOOP,
	ERROR // NOOP value for state machines et.c.
};