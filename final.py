from collections import deque
f, pages, frames = 0, open('pages.txt','r').read().replace('\n',''), deque([])
for index, p in enumerate(pages):
	print 'loading',p
	if len(['' for item in frames if p in item]): 
		print 'page already loaded'
	else:
		print 'page fault'
		if len(frames) is 4: print 'fifo ejecting',frames.popleft()
		frames.append(tuple([p,index]))
		f += 1
	print 'page frame queue:',list(frames)
print 'total page faults:',f