import React, { useState, useEffect } from 'react';
import { Helmet } from 'react-helmet';
import { useSelect } from 'downshift';
import { ChevronDownIcon } from '@heroicons/react/20/solid';
import './App.css';
import iGEMLogo from './assets/iGEM_logo.svg';
import { Popup } from 'reactjs-popup';

const App: React.FC = () => {
  const [selectedMode, setSelectedMode] = useState<string>('Off');
  const [selectedNode, setSelectedNode] = useState<number>(0);
  const {
    isOpen,
    getToggleButtonProps,
    getItemProps,
    getMenuProps,
    highlightedIndex,
    selectedItem,
  } = useSelect({
    items: ['Port 1', 'Port 2'],
    onSelectedItemChange: (changes) => console.log(changes.selectedItem),
  });
const [selectedSensor, setSelectedSensor] = useState<string>('DHT11'); // Default sensor
  const {
    isOpen: sensorIsOpen,
    getToggleButtonProps: getSensorToggleButtonProps,
    getItemProps: getSensorItemProps,
    getMenuProps: getSensorMenuProps,
    highlightedIndex: sensorHighlightedIndex,
    selectedItem: sensorSelectedItem,
  } = useSelect({
    items: ['DHT11', 'OD600'],
    onSelectedItemChange: (changes) => {
      setSelectedSensor(changes.selectedItem);
      console.log("Selected Sensor:", changes.selectedItem);
    },
  });
  const [isPopupOpen, setIsPopupOpen] = useState(false);

const handleAdvancedSettingsClick = () => {
    setIsPopupOpen(true);
  };

  const handleModeChange = (mode: string) => {
    setSelectedMode(mode);
  };

  const handleNodeClick = (index: number) => {
    setSelectedNode(index);
  };

  const nodeStyles = (index: number) => ({
    width: '20px',
    height:'20px',
    backgroundColor: selectedNode === index ? '#000' : '#fff',
    fontWeight: selectedNode === index ? 'bold' : 'normal',
    fontSize: '1.5rem',
    top: `${(index / 3 * 20) + 10}rem`,
  });

  return (
    <div className="app">
    <header className="header">
    <img rel="icon" src={iGEMLogo} alt="UBC iGEM Logo" className="logo" />
    <div className="dropdown-container">
    <button {...getToggleButtonProps()} className="dropdown-button">
    {selectedItem || 'Select Port'}
    <ChevronDownIcon className="dropdown-arrow" />
    </button>
    <ul
               {...getMenuProps()}
               className={'dropdown-menu ' + (isOpen ? 'open' : '')}
    >
    {isOpen &&
      ['Port 1', 'Port 2'].map((item, index) => (
        <li
          key={item}
          {...getItemProps({ item, index })}
          className={'dropdown-item ' + (highlightedIndex === index ? 'highlighted' : '')}
        >
        {item}
        </li>
      ))}
      </ul>
      </div>
      </header>

      <main className="main">
      <section className="controls">
      <div className="vertical-line"></div> 
      <div
					      className="node"
					      onClick={() => handleNodeClick(0)}
					      style={nodeStyles(0)}
      >
      <span>Off</span>
      </div>
      <div
              className="node"
              onClick={() => handleNodeClick(1)}
              style={nodeStyles(1)}
      >
      <span>Mixing mode</span>
      </div>
      <div
              className="node"
              onClick={() => handleNodeClick(2)}
              style={nodeStyles(2)}
      >
      <span>Bubbling mode</span>
      </div>
      <div
              className="node"
              onClick={() => handleNodeClick(3)}
              style={nodeStyles(3)}
      >
      <span>Fluid out</span>
      </div>
<button className="advanced-settings-button" onClick={handleAdvancedSettingsClick}>
            Advanced Settings
          </button>

          {/* Popup */}
          <Popup open={isPopupOpen} onClose={() => setIsPopupOpen(false)}>
            <div className="popup-content">
              {/* Add content to your popup here */}
              {/* For now, just a close button */}
              <button onClick={() => setIsPopupOpen(false)}>Close</button>
            </div>
          </Popup>
      </section>

      <section className="display">
<div className="sensor-dropdown-container">
          <div
            {...getSensorToggleButtonProps()}
            className="sensor-title"
          >
            <strong>{sensorSelectedItem || 'Sensor'}</strong>
            <ChevronDownIcon
              className="dropdown-arrow"
              style={{
                transform: sensorIsOpen ? 'rotate(180deg)' : 'rotate(0deg)',
                transition: 'transform 0.2s ease', 
              }}
            />
            </div>
	    <ul
            {...getSensorMenuProps()}
            className={'dropdown-menu ' + (sensorIsOpen ? 'open' : '')}
          >
            {sensorIsOpen &&
              ['DHT11', 'OD600'].map((item, index) => (
                <li
                  key={item}
                  {...getSensorItemProps({ item, index })}
                  className={
                    'dropdown-item ' +
                    (sensorHighlightedIndex === index ? 'highlighted' : '')
                  }
                >
                  {item}
                </li>
              ))}
          </ul>
          </div>
	  </section>
      </main>
      <Helmet>
      <title>BioRX Control Panel | MK3</title>
      <link rel="icon" href={iGEMLogo} class="icon" />
      </Helmet>
      </div>
  );
};

export default App;
