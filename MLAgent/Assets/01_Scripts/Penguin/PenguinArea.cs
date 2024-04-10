using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PenguinArea : MonoBehaviour
{
	public PenguinAgent penguinAgent;
	public GameObject penguinBaby;
	public Fish fishPrefab;
	public TextMeshPro cumulativeRewarddTxt;

	private List<GameObject> fishList;

	public int remainingFish { get { return fishList.Count; } }


	public static Vector3 ChooseRandomPosition(Vector3 center, float minAngle, float maxAngle, float minRadius, float maxRadius)
	{
		float randomAngle = Random.Range(minAngle, maxAngle);
		float randomRadius = Random.Range(minRadius, maxRadius);

		return center + Quaternion.Euler(0, randomAngle, 0) * Vector3.forward * randomRadius;
	}

	private void PlacePenguin()
	{
		Rigidbody rigidbody = penguinAgent.GetComponent<Rigidbody>();
		rigidbody.velocity = Vector3.zero;
		rigidbody.angularVelocity = Vector3.zero;

		penguinAgent.transform.position = ChooseRandomPosition(transform.parent.position, 0, 360, 0, 9) + Vector3.up * 0.5f;
		penguinAgent.transform.rotation = Quaternion.Euler(0, Random.Range(0, 360f), 0);
	}

	private void PlaceBaby()
	{
		Rigidbody rigidbody = penguinBaby.GetComponent<Rigidbody>();
		rigidbody.velocity = Vector3.zero;
		rigidbody.angularVelocity = Vector3.zero;

		penguinBaby.transform.position = ChooseRandomPosition(transform.parent.position, -45, 45, 4, 9) + Vector3.up * 0.5f;
		penguinBaby.transform.rotation = Quaternion.Euler(0, 180, 0);
	}

	private void SpawnFish(int count)
	{
		for (int i = 0; i < count; i++)
		{
			GameObject fishObject = Instantiate(fishPrefab.gameObject);
			fishObject.transform.position = ChooseRandomPosition(transform.parent.position, 100, 260, 2, 13) + Vector3.up * 0.5f;
			fishObject.transform.rotation = Quaternion.Euler(0, Random.Range(0, 360f), 0);
			fishObject.transform.SetParent(transform);

			fishList.Add(fishObject);
		}
	}

	private void RemoveAllFish()
	{
		if (fishList != null)
		{
			foreach (GameObject obj in fishList)
			{
				Destroy(obj);
			}
		}
		fishList = new List<GameObject>();
	}

	public void RemoveFishInList(GameObject fish)
	{
		fishList.Remove(fish);
		Destroy(fish);
	}

	public void ResetArea()
	{
		RemoveAllFish();
		PlacePenguin();
		PlaceBaby();
		SpawnFish(5);
	}

	private void FixedUpdate()
	{
		cumulativeRewarddTxt.text = penguinAgent.GetCumulativeReward().ToString("0.00");
	}
}
