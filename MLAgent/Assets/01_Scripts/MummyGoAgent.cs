using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;
using Unity.MLAgents.Sensors;

public class MummyGoAgent : Agent
{
	public GameObject target;

	public MeshRenderer floor;

	private float x, y = 0;
	private bool isWall = false;
	private bool isTarget = false;

	public override void Initialize()
	{
	}

	public override void OnEpisodeBegin()
	{
		isWall = false;
		isTarget = false;
		floor.material.color = Color.gray;
		x = Random.Range(-4.5f, 4.5f);
		y = Random.Range(-4.5f, 4.5f);
		target.transform.localPosition = new Vector3(x, 0.55f, y);

		x = Random.Range(-4.5f, 4.5f);
		y = Random.Range(-4.5f, 4.5f);
		transform.localPosition = new Vector3(x, 0.55f, y);
	}

	public override void CollectObservations(VectorSensor sensor)
	{
		sensor.AddObservation(transform.position.x);
		sensor.AddObservation(transform.position.z);
		sensor.AddObservation(target.transform.position);
	}

	public override void OnActionReceived(ActionBuffers actions)
	{
		var ContinuousActions = actions.ContinuousActions;
		float x = Mathf.Clamp(ContinuousActions[0], -1f, 1f);
		float z = Mathf.Clamp(ContinuousActions[1], -1f, 1f);

		transform.localPosition += new Vector3(x, 0f, z) * 3;

		if (isWall)
		{
			SetReward(-1f);
			floor.material.color = Color.red;
			EndEpisode();
		}
		else if (isTarget)
		{
			SetReward(1f);
			floor.material.color = Color.blue;
			EndEpisode();
		}
		else if(transform.localPosition.y < -3)
		{
			SetReward(-1f);
			EndEpisode();
		}
		else
		{
			SetReward(0.1f);
		}
	}

	public override void Heuristic(in ActionBuffers actionsOut)
	{
		var ContinuousActionOut = actionsOut.ContinuousActions;
		ContinuousActionOut[0] = Input.GetAxis("Horizontal");
		ContinuousActionOut[1] = Input.GetAxis("Vertical");
	}

	private void OnCollisionEnter(Collision collision)
	{
		if (collision.collider.tag == "Wall")
			isWall = true;

		if (collision.collider.tag == "Target")
			isTarget = true;
	}
}
