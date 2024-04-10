using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class Fish : MonoBehaviour
{
	private float fishSpeed;
	private float nextActionTime = -1;
	private Vector3 targetPosition;

	private void FixedUpdate()
	{
		Swin();
	}

	private void Swin()
	{
		if (Time.fixedTime >= nextActionTime)
		{
			// 새로운 위치를 타겟팅하고, nextActionTime을 세팅한다
			fishSpeed = Random.Range(0.4f, 1f);
			targetPosition = PenguinArea.ChooseRandomPosition(transform.parent.position, 100, 260, 2, 13);

			transform.rotation = Quaternion.LookRotation(targetPosition - transform.position);

			float timeToTarget = Vector3.Distance(transform.position, targetPosition) / fishSpeed;
			nextActionTime = Time.fixedTime + timeToTarget;
		}
		else
		{
			// 타겟팅한 위치를 향해 이동한다
			transform.position += transform.forward * fishSpeed * Time.fixedDeltaTime;
		}
	}
}