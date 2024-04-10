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
			// ���ο� ��ġ�� Ÿ�����ϰ�, nextActionTime�� �����Ѵ�
			fishSpeed = Random.Range(0.4f, 1f);
			targetPosition = PenguinArea.ChooseRandomPosition(transform.parent.position, 100, 260, 2, 13);

			transform.rotation = Quaternion.LookRotation(targetPosition - transform.position);

			float timeToTarget = Vector3.Distance(transform.position, targetPosition) / fishSpeed;
			nextActionTime = Time.fixedTime + timeToTarget;
		}
		else
		{
			// Ÿ������ ��ġ�� ���� �̵��Ѵ�
			transform.position += transform.forward * fishSpeed * Time.fixedDeltaTime;
		}
	}
}