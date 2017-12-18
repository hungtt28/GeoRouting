
import re
import json
#{"e":"S","p_id":0,"p_type":"normal","source":1172,"dest":670,"cur":1172,"layer":"network","time":10.012041273144}
#25.316273464295   SN.node[936].Communication.Routing       SEND      PACKET #0         FROM 273       TO 1328      currentHop 936       nextHop 972  
def main():
	data = open('Castalia-Trace.txt', 'rb').readlines()
	trace = ''
	for line in data:
		m = re.match(r"(?P<time>[^\s]+)(\s+)(?P<layer>[^\s]+)(\s+)(?P<e>[^\s]+)(\s+)PACKET(\s+)#(?P<p_id>\d+)(\s+)FROM(\s+)(?P<source>\d+)(\s+)TO(\s+)(?P<dest>\d+)(\s+)currentHop(\s+)(?P<cur>\d+).*", line)
		if (m):
			d = m.groupdict()
			if (d['e'] == 'SEND' or (d['e'] == 'RECEIVE' and d['dest'] == d['cur'])):
				if (d['source'] == d['cur']):
					d['e'] = 'S'
				elif (d['dest'] == d['cur']):
					d['e'] = 'R'
				else:
					d['e'] = 'F'
				d['p_type'] = 'normal'
				d['layer'] = 'network'
				trace += '{}\n'.format(json.dumps(d))
			
	open('trace.log', 'wb').write(trace)
	return

if __name__ == "__main__":
	main()