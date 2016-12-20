
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include "MQTTClient.h"
#include <time.h>

#define ADDRESS     "tcp://37.187.106.16:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC1      "paho_sub"
#define	TOPIC2	    "paho_pub"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
int rc;
int ch;
volatile MQTTClient_deliveryToken deliveredtoken;


MQTTClient client;
MQTTClient_message pubmsg = MQTTClient_message_initializer;
MQTTClient_deliveryToken token;
/*void create_client()
{





}*/
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void mqtt_subscribe()
{


    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC2, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC2, QOS);

    do 
    {
        ch = getchar();
    } while(ch!='Q' && ch != 'q');

}

void mqtt_publish()
{
char *msg = NULL;
size_t size = 0;

/* Open your_file in read-only mode */
FILE *fp = fopen("test2.txt", "r");

/* Get the buffer size */
fseek(fp, 0, SEEK_END); /* Go to end of file */
size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
msg = malloc((size + 1) * sizeof(*msg)); /* size + 1 byte for the \0 */

// Print the array size
printf("Size of the array is %lu\n", size);

/* Read the file into the buffer */
fread(msg, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
msg[size] = '\0';

/* Print it ! */
//printf("%s\n", buffer);
//msg[1024]= buffer[size];
//printf("%s", msg);

   pubmsg.payload = msg;
    pubmsg.payloadlen = strlen(msg);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    MQTTClient_publishMessage(client, TOPIC1, &pubmsg, &token);
    printf("Waiting for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            msg, TOPIC1, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
}


int main(int argc, char* argv[])
{

MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);       
    }
else
{
printf("Connected to IP successfully");
}

    //mqtt_publish();
    //sleep(1);
    mqtt_subscribe();
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}


