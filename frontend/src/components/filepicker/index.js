import { h } from "preact";
import { useState } from 'preact/hooks';

import './style.scss';


const FilePicker = ({ onChange = () => true, onUpload = () => true, accept="*.*", noFile = "Bitte wählen sie eine Datei aus!", ...rest }) => {
  const [ fileUpload, setFileUpload ] = useState();
  const [ selectedFile, setSelectedFile ] = useState();
  
  const clearFile = () => {
    setSelectedFile();
  }

  const selectFile = ({ target }) => {
    const { files } = target;
    const [ file, ...f ] = files;

    if (file) {
      setSelectedFile(file);
      onChange(file);
    }
  }

  return (
    <div className="row">
      <div className="col-sm-12">
        <div className="filecontainer" >
          <button className="small" onClick={() => fileUpload.click()} {...rest}>Auswählen...</button>
          {selectedFile && <button className="small" onClick={() => onUpload(clearFile)} {...rest}>Hochladen</button>}
          <p className="vertical">{selectedFile ? selectedFile.name : noFile}</p>
        </div>
      </div>
      <input type="file" accept={accept} className="picker" onChange={selectFile} ref={(el) => setFileUpload(el) }/>

    </div>
  );
}

export default FilePicker;