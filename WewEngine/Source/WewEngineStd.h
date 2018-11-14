#pragma once

#include <map>
#include <string>
#include <memory>

#include "tinyxml2.h"
#include "Logger.h"

#pragma warning(disable: 4221)
#pragma warning(disable: 4006)

class Actor;
class ActorComponent;
class ActorFactory;

typedef unsigned long ActorId;
typedef unsigned long ComponentId;

typedef ActorComponent* (*ActorComponentCreator)(void);
typedef std::map<std::string, ActorComponentCreator> ActorComponentCreatorMap;

typedef unsigned long ActorId;
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;

typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;

#define KILOBYTES(x) (x * 1024)
#define MEGABYTES(x) (KILOBYTES(x) * 1024)
#define GIGABYTES(x) (MEGABYTES(x) * 1024)