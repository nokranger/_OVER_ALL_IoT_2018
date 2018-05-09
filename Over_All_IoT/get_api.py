import requests
import json
#r1 = requests.get('http://172.16.157.190:4000/getstudent')
r2 = requests.post('http://172.16.157.190:4000/poststudent', json = {'name':'hahaha', 'id' : '12345678'})
#print (r1.status_code)

print (r2.status_code)
print (r2.text)
#jsondata = r1.json()
#print (jsondata[0]['name'])
                                                                                                                              v
