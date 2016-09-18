#ifndef MODELFILEREADER_H
#define MODELFILEREADER_H


class ModelFileReader {
    public:
        
        ModelFileReader();
        
        virtual ~ModelFileReader();
        
        Model readModel(std::string fileName);
        
    protected:
        
    private:
        //TODO: support for .obj https://en.wikipedia.org/wiki/Wavefront_.obj_file
        Model readOBJ(); //reads .obj files
        
};

#endif // MODELFILEREADER_H
