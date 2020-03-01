using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    float verticalMovement;
    float horizontalMovement;
    [SerializeField] float speed;
    Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = gameObject.GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {

        verticalMovement = Input.GetAxis("Vertical");
        horizontalMovement = Input.GetAxis("Horizontal");

        //up arrow key
        if (Input.GetKey("w"))
        {
            rigidbody.MovePosition((Vector3)rigidbody.position + Vector3.forward * verticalMovement * speed * Time.deltaTime);
        }

        //down arrow key
        if (Input.GetKey("s"))
        {
            rigidbody.MovePosition((Vector3)rigidbody.position - Vector3.back * verticalMovement * speed * Time.deltaTime);
        }

        //right arrow key
        if (Input.GetKey("d"))
        {
            rigidbody.MovePosition((Vector3)rigidbody.position + Vector3.right * horizontalMovement * speed * Time.deltaTime);
        }

        //left arrow key
        if (Input.GetKey("a"))
        {
            rigidbody.MovePosition((Vector3)rigidbody.position - Vector3.left * horizontalMovement * speed * Time.deltaTime);
        }

    }
}
