import os
import sys

forms = ['_tsk.c','_tsk.h','_api.c','_api.h']

def listFiles(path, ext):
	lista = []
	for pasta, subPastas, arquivos  in os.walk(path):
		for item in ext:
			lista.extend([os.path.join(pasta,arquivo) for arquivo in arquivos if arquivo.endswith(item) and not arquivo in forms])
	return lista

def SerializeFSM(fsmString):
	result =[]
	buffer = ''
    
	# Remove comentários simples
	for line in fsmString.split('\n'):
		pos = line.find('//')
		if pos == -1:
			pos = len(line)
		buffer = buffer+line[0:pos] #+ '\n'
	
	# Remove comentários em blocos
	while buffer.find('/*') != -1:
		start = buffer.find('/*')
		end = buffer.find('*/')+2
		buffer = buffer[0:start] + buffer[end:len(buffer)]
	
	# Remove caracteres desnecessários para gerar a FSM
	remove = ['(void*)',' ', '\t']
	for test in remove:
		while buffer.find(test) != -1:
			pos = buffer.find(test)
			buffer = buffer[0:pos] + buffer[pos+len(test):len(buffer)]
	
	# Quebra as linhas da maquina de estado
	split = []
	while buffer.find('{') != -1:
		start = buffer.find('{')
		end = buffer.find('}')+1
		split.append(buffer[start:end])
		buffer = buffer[0:start] + buffer[end:len(buffer)]
	for line in split:
		result.append(line.replace('{','').replace('}','').split(','))
	return result
	
def generateFSM(tuple):
	graph='graph TD\n'
	for line in tuple:
		if line[0] != 'NULL':
			graph = graph + '  ' + line[0] + ' -->|' + line[1] + '| ' + line[2] + '\n'
	return graph

def generateMermaidCode(code,file):
	f = open(file,'w+')
	f.write(code)
	f.close()
	
def generateMermaidHTML(code,file):
	f = open(file,'w+')
	f.write('<html><body><script src="https://cdn.jsdelivr.net/npm/mermaid@8.4.0/dist/mermaid.min.js"></script><script>mermaid.initialize({startOnLoad:true});</script><div class="mermaid">\n')
	f.write(code)
	f.write('</div></body></html>')
	f.close()
	
def generateGraphFromSourceCode():
	lista = listFiles(os.path.abspath('..'), ['.c','.h'])
	count=0
	for item in lista:
		file = open(item, "rt")
		contents = file.read()
		file.close()
		index=0
		pattern = 'static fsm_state_t '
		while index<len(contents):
			index = contents.find(pattern, index)
			if index == -1:
				break
			index = index + len(pattern)
			stateTableName = contents[index:contents.find('[', index)]
			print('Generating ' + stateTableName + ' FSM in ' + str(item) + '\n')
			count = count+1
			index = contents.find('{', index) + 1
			key = 1
			pos = 0
			while key > 0:
				if(contents[index + pos] == '{'):
					key = key+1
				elif (contents[index + pos] == '}'):
					key = key-1
				pos = pos+1
			machine = generateFSM(SerializeFSM(contents[index:index+pos]))
			if os.path.exists(os.path.abspath('../docs/')) == 0:
				os.mkdir(os.path.abspath('../docs/'))
			generateMermaidHTML(machine, os.path.abspath('../docs/' + stateTableName + '.html'))
			generateMermaidCode(machine, os.path.abspath('../docs/' + stateTableName + '.txt'))
	print('Generated ' + str(count) + ' FSM machines in ' + os.path.abspath('../docs/') + '\n')

def generateSourceCodeFromGraph(fsmName, fsmStart, fsmTable, fsmEvList, functionList, fsmTransitions):    
	if not os.path.exists(os.path.abspath(fsmName)):
		os.mkdir(os.path.abspath(fsmName))

	for file in forms:
		print('Generating ' + fsmName + file + ' file\n')
		f = open(os.path.abspath('src/'+file),'r')
		contents = f.read()
		f.close()
		
		# $FSM_NAME$
		index=0
		pattern='$FSM_NAME$'
		result = ''
		index = contents.find(pattern, index)
		while index != -1:
			contents = contents[0:index] + fsmName + contents[index+len(pattern):len(contents)]
			index = contents.find(pattern, index)
		
		# $FSM_START_CB$
		pattern='$FSM_START_CB$'
		index = contents.find(pattern, 0)
		if index > 0:
			contents = contents[0:index] + fsmStart + contents[index+len(pattern):len(contents)]
			
		# $FSM_TABLE$
		pattern='$FSM_TABLE$'
		index = contents.find(pattern, 0)
		if index > 0:
			contents = contents[0:index] + fsmTable + contents[index+len(pattern):len(contents)]
		
		# $FSM_EVENT_LIST$
		pattern='$FSM_EVENT_LIST$'
		index = contents.find(pattern, 0)
		if index > 0:
			result = ''
			for event in fsmEvList:
				result = result + event + ',\n  '
			contents = contents[0:index] + result + contents[index+len(pattern):len(contents)]
		
		# $FSM_PROTOTYPE$
		pattern='$FSM_PROTOTYPE$'
		index = contents.find(pattern, 0)
		if index > 0:
			result = ''
			for function in functionList:
				result = result + '/**\n * @brief ' + function + '\n */\n' + fsmName + '_evHandler ' + function + '(fsm_handler_t* this);\n\n'
			contents = contents[0:index] + result + contents[index+len(pattern):len(contents)]

		# $FSM_FUNCTION$
		pattern='$FSM_FUNCTION$'
		index = contents.find(pattern, 0)
		if index > 0:
			result = ''
			for function in functionList:
				data = ''
				for state in fsmTransitions:
					if state[0] == function:
						data = data + '\n  if(0)\n    return ' + state[1] + ';'
				result = result + fsmName + '_evHandler ' + function + '(fsm_handler_t* this)\n{' + data + '\n}\n\n'
			contents = contents[0:index] + result + contents[index+len(pattern):len(contents)]        
			
		f = open(os.path.abspath(fsmName + '/' + fsmName + file),'w')
		f.write(contents)
		f.close()
	print('\nGenerated ' + fsmName + ' FSM machine in ' + os.path.abspath(fsmName) + '\n')

# Recebe os argumentos enviados via linha de comando
if len(sys.argv) > 1:
	#try:
		f = open(os.path.abspath(sys.argv[1]),'r')
		descriptor = f.read()
		f.close()
		
		lines = descriptor.split('\n')
		fsmName = sys.argv[1][0:sys.argv[1].index('.')]
		fsmStart = ''
		fsmTable = ''
		fsmEvList = []
		functionList = []
		fsmTransitions = []
		for line in lines:
			par = line.split(',')
			state = fsmName + '_' + par[0].strip()
			event = fsmName + '_' + par[1].strip()
			callback = fsmName + '_' + par[2].strip()
			fsmTransitions.append([state,event,callback])
			fsmTable = fsmTable + '{ (void*)' + state + ', ' + event + ', (void*)' + callback + ' },\n  '
			if fsmStart == '':
				fsmStart = state
			if not event in fsmEvList:
				print(event)
				fsmEvList.append(event)
			if not state in functionList:
				functionList.append(state)
			if not callback in functionList:
				functionList.append(callback)
		generateSourceCodeFromGraph( fsmName,fsmStart,fsmTable,fsmEvList,functionList,fsmTransitions )
	#except:
	#    print ('Unexpected error:', sys.exc_info())
	#except:
	#    print('Impossível abrir o arquivo ' + sys.argv[1])
else:
	generateGraphFromSourceCode()