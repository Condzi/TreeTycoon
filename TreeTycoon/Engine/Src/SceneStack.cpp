/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "SceneStack.hpp"

namespace con::priv
{
std::unique_ptr<Scene> SceneFactory::createScene( SceneID id )
{
	auto result = functions.find( id );
	if ( result != functions.end() )
		return result->second();

	log( LogPriority::Error, "no scene of id \"", id, "\"." );
	return nullptr;
}

void SceneStackClass::push( SceneID id )
{
	requestAction( { Operation::Push, id } );
}

void SceneStackClass::pop()
{
	requestAction( { Operation::Pop, 0 } );
}

void SceneStackClass::enableCurrentScene()
{
	requestAction( { Operation::Enable, 0 } );
}

void SceneStackClass::disableCurrentScene()
{
	requestAction( { Operation::Disable, 0 } );
}

std::optional<SceneStackClass::SceneID> SceneStackClass::getSceneOnTop()
{

	return std::optional<SceneID>();
}

void SceneStackClass::requestAction( Action&& action )
{
	static auto getOperationAsString = []( Operation op ) {
		switch ( op ) {
		case Operation::Push: return "Push";
		case Operation::Pop: return "Pop";
		case Operation::Enable: return "Enable";
		case Operation::Disable: return "Disable";
		}
	};

	if ( action.operation == Operation::Push )
		log( LogPriority::Info, "request \"Push\", id \"", action.scene, "\"." );
	else
		log( LogPriority::Info, "request \"", getOperationAsString( action.operation ), "\"." );

	pendingActions.emplace_back( std::move( action ) );
}

void SceneStackClass::applyPush( SceneID id )
{
	auto scene = factory.createScene( id );
	if ( scene ) {
		log( LogPriority::Info, "scene Push, id \"", id, "\"." );
		scenes.emplace_back( std::move( scene ) )->onPush();
	} else
		log( LogPriority::Info, "failed to Push, id \"", id, "\"." );
}

void SceneStackClass::applyPop()
{
	if ( scenes.empty() )
		return log( LogPriority::Error, "failed to Pop: empty stack." );

	log( LogPriority::Info, "scene Pop." );
	scenes.back()->onPop();
	scenes.pop_back();
}

void SceneStackClass::applyEnable()
{
	if ( scenes.empty() )
		return log( LogPriority::Error, "failed to Enable current scene: empty stack." );

	scenes.back()->_enable();
}

void SceneStackClass::applyDisable()
{
	if ( scenes.empty() )
		return log( LogPriority::Error, "failed to Disable current scene: empty stack." );

	scenes.back()->_disable();
}

void SceneStackClass::applyActions()
{
	// Action is that small it's not worth using reference
	for ( auto action : pendingActions ) {
		switch ( action.operation ) {
		case Operation::Push: applyPush( action.scene ); break;
		case Operation::Pop: applyPop(); break;
		case Operation::Enable: applyEnable(); break;
		case Operation::Disable: applyDisable(); break;
		}
	}

	pendingActions.clear();
}

void SceneStackClass::updateScenes()
{
	for ( auto& scene : scenes )
		scene->_update();
}

void SceneStackClass::update()
{
	applyActions();
	updateScenes();
}
}