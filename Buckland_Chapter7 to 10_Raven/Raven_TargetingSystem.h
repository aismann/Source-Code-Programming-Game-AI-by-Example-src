#ifndef TARGETING_SYSTEM_H
#define TARGETING_SYSTEM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_TargetingSystem.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to select a target from the opponents currently in a bot's
//          perceptive memory.
//-----------------------------------------------------------------------------
#include "../Common/2D/Vector2D.h"
#include <list>


class Raven_Bot;

enum TargetSelectionCriteria
{
	default = 0,
	closer_distance = 1,
	most_damaged_enemy = 2,
	most_damaged_received = 3,
	invalid = 4,

};



class Raven_TargetingSystem
{
private:

  //the owner of this system
  Raven_Bot*  m_pOwner;

  //the current target (this will be null if there is no target assigned)
  Raven_Bot*  m_pCurrentTarget;

  //the current criteria to select the target
  TargetSelectionCriteria m_currentCriteria;

public:

  Raven_TargetingSystem(Raven_Bot* owner, TargetSelectionCriteria criteria  = TargetSelectionCriteria::default);

  //each time this method is called the opponents in the owner's sensory 
  //memory are examined and the closest  is assigned to m_pCurrentTarget.
  //if there are no opponents that have had their memory records updated
  //within the memory span of the owner then the current target is set
  //to null
  void       Update();

  //returns true if there is a currently assigned target
  bool       isTargetPresent()const{return m_pCurrentTarget != 0;}

  //returns true if the target is within the field of view of the owner
  bool       isTargetWithinFOV()const;

  //returns true if there is unobstructed line of sight between the target
  //and the owner
  bool       isTargetShootable()const;

  //returns the position the target was last seen. Throws an exception if
  //there is no target currently assigned
  Vector2D   GetLastRecordedPosition()const;

  //returns the amount of time the target has been in the field of view
  double      GetTimeTargetHasBeenVisible()const;

  //returns the amount of time the target has been out of view
  double      GetTimeTargetHasBeenOutOfView()const;
  
  double Raven_TargetingSystem::GetTotalDamageReceived(Raven_Bot* pOpponent)const;


  //returns total damage received by a current target
  double Raven_TargetingSystem::GetTotalDamageReceived()const;


  //returns a pointer to the target. null if no target current.
  Raven_Bot* GetTarget()const{return m_pCurrentTarget;}

  //sets the target pointer to null
  void       ClearTarget(){m_pCurrentTarget=0;}
};




#endif
