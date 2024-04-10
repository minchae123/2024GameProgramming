using Google.Protobuf.Collections;
using System.Collections;
using System.Collections.Generic;
using Unity.MLAgents;
using Unity.MLAgents.Actuators;
using Unity.MLAgents.Sensors;
using UnityEngine;

public class PenguinAgent : Agent
{
	public float moveSpeed = 5f;
	public float turnSpeed = 180f;
	public GameObject heartPrefab;
	public GameObject regurgitatedFishPrefab;

	private PenguinArea penguinArea;
	private new Rigidbody rigidbody;
	private GameObject babyPenguin;

	private bool isFull;


	public override void Initialize()
	{
		penguinArea = transform.parent.Find("PenguinArea").GetComponent<PenguinArea>();
		babyPenguin = penguinArea.penguinBaby;
		rigidbody = GetComponent<Rigidbody>();
	}

	public override void OnEpisodeBegin()
	{
		isFull = false;
		penguinArea.ResetArea();
	}

	public override void CollectObservations(VectorSensor sensor)
	{
		// 관측개수 8
		sensor.AddObservation(isFull);
		sensor.AddObservation(Vector3.Distance(transform.position, babyPenguin.transform.position));
		sensor.AddObservation((babyPenguin.transform.position - transform.position).normalized);
		sensor.AddObservation(transform.forward);
	}

	public override void OnActionReceived(ActionBuffers actions)
	{
		var DiscreteActions = actions.DiscreteActions;

		// 앞으로 가지 않을지(0) 앞으로 갈지(1)
		float fowardAmount = DiscreteActions[0];

		// 회전을 안할지(0), 왼쪽으로 회전(1), 오른쪽 회전(2)
		float turnAmount = 0f;
		if (DiscreteActions[1] == 1)
		{
			turnAmount = -1f;
		}
		else if (DiscreteActions[1] == 2)
		{
			turnAmount = 1f;
		}

		rigidbody.MovePosition(transform.position + transform.forward * fowardAmount * moveSpeed * Time.fixedDeltaTime);
		transform.Rotate(Vector3.up * turnAmount * turnSpeed * Time.fixedDeltaTime);

		AddReward(-1f / MaxStep);
	}

	public override void Heuristic(in ActionBuffers actionsOut)
	{
		var DiscreateActionsOut = actionsOut.DiscreteActions;

		if (Input.GetKey(KeyCode.W))
		{
			DiscreateActionsOut[0] = 1;
		}
		else if (Input.GetKey(KeyCode.A))
		{
			DiscreateActionsOut[1] = 1;

		}
		else if (Input.GetKey(KeyCode.D))
		{
			DiscreateActionsOut[1] = 2;
		}
	}

	private void OnCollisionEnter(Collision collision)
	{
		if (collision.collider.CompareTag("Fish"))
		{
			EatFish(collision.gameObject);
		}
		else if (collision.collider.CompareTag("BabyPenguin"))
		{
			RegurgitateFish();
		}
	}

	private void EatFish(GameObject fish)
	{
		if (isFull) return;
		isFull = true;
		penguinArea.RemoveFishInList(fish);
		AddReward(1);
	}

	private void RegurgitateFish()
	{
		if (!isFull) return;
		isFull = false;

		GameObject regurgiateFish = Instantiate(regurgitatedFishPrefab, transform.parent);
		regurgiateFish.transform.localPosition = babyPenguin.transform.localPosition + Vector3.up * 0.01f;
		Destroy(regurgiateFish, 4f);

		GameObject heart = Instantiate(heartPrefab, transform.parent);
		heart.transform.localPosition = babyPenguin.transform.localPosition + Vector3.up;
		Destroy(heart, 4f);

		AddReward(1);

		if(penguinArea.remainingFish <= 0)
		{
			EndEpisode();
		}

	}
}
