using System.Collections;
using System.Collections.Generic;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;
using Unity.MLAgents.Sensors;
using UnityEngine;

public class PenguinAgent : Agent
{
	public override void Initialize()
	{
		base.Initialize();
	}

	public override void OnEpisodeBegin()
	{
		base.OnEpisodeBegin();
	}

	public override void CollectObservations(VectorSensor sensor)
	{
		base.CollectObservations(sensor);
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
