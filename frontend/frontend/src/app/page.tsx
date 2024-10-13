import Image from "next/image";
import Link from "next/link";

export default function Home() {
  return (
    <>
    <nav className="navbar">
      <div className="navbar-container">
        <Link href="/" className="navbar-logo">
        iDevice
        </Link>
      </div>
    </nav>
    </>
  );
}
