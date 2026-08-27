import sys

try:
	import unittest
except:
	print("***********************************************************")
	print("* WARNING!! Couldn't import python unittesting framework! *")
	print("* No python tests have been executed                      *")
	print("***********************************************************")
	sys.exit(0)

try:
	import crpropa
except Exception as e:
	print("*** CRPropa import failed")
	print(type(e), str(e))
	sys.exit(-1)

class testImports(unittest.TestCase):
	def testImports(self):
		crpropa.declare_version
		crpropa.particleMass
		crpropa.nuclearMass
		crpropa.nucleusId
		crpropa.chargeNumber
		crpropa.massNumber
		crpropa.isNucleus
		crpropa.convertIdToName
		crpropa.logError
		crpropa.logInfo
		crpropa.logWarning
		crpropa.logDebug
		crpropa.setLogStream
		crpropa.setLogLevel
		crpropa.meanFieldVector
		crpropa.meanFieldStrength
		crpropa.rmsFieldStrength
		crpropa.rmsFieldStrengthPerAxis
		crpropa.scaleGrid
		crpropa.fromMagneticField
		crpropa.fromMagneticFieldStrength
		crpropa.loadGrid
		crpropa.dumpGrid
		crpropa.loadGrid3fFromTxt
		crpropa.loadGridFromTxt
		crpropa.loadGrid1fFromTxt
		crpropa.dumpGridToTxt
		crpropa.gridPowerSpectrum
		crpropa.periodicClamp
		crpropa.reflectiveBoundary
		crpropa.periodicBoundary
		crpropa.reflectiveClamp
		crpropa.round
		crpropa.setCosmologyParameters
		crpropa.hubbleRate
		crpropa.omegaL
		crpropa.omegaM
		crpropa.H0
		crpropa.comovingDistance2Redshift
		crpropa.redshift2ComovingDistance
		crpropa.luminosityDistance2Redshift
		crpropa.redshift2LuminosityDistance
		crpropa.lightTravelDistance2Redshift
		crpropa.redshift2LightTravelDistance
		crpropa.comoving2LightTravelDistance
		crpropa.lightTravel2ComovingDistance
		crpropa.getDataPath
		crpropa.getInstallPrefix
		crpropa.digit
		# crpropa.clip
		crpropa.interpolate
		crpropa.interpolate2d
		crpropa.interpolateEquidistant
		crpropa.closestIndex
		crpropa.splitFilename
		# crpropa.pow_integer
		# crpropa.gaussInt
		crpropa.initHelicalTurbulence
		crpropa.initTurbulence
		crpropa.turbulentCorrelationLength

if __name__ == '__main__':
	unittest.main()