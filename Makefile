SOURCES :=  $(wildcard $(shell find src -type f -name '*.cpp'))
INCLUDES := src/
OBJS    :=  $(patsubst %.cpp, build/%.o, $(SOURCES))

.PHONY: compiler clean

compiler: $(OBJS)
	$(CXX) -o $@ $(OBJS) -I$(INCLUDES)

$(OBJS) : build/%.o: %.cpp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $< -o $@
