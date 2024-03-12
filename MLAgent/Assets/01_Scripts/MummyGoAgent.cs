using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;

public class MummyGoAgent : Agent
{
	public override void Initialize()
	{
		base.Initialize();
	}

	public override void OnEpisodeBegin()
	{
		base.OnEpisodeBegin();
	}

	public override void OnActionReceived(ActionBuffers actions)
	{
		base.OnActionReceived(actions);
	}

	public override void Heuristic(in ActionBuffers actionsOut)
	{
		base.Heuristic(actionsOut);
	}
}
